// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvancedDeletionWidget.h"
#include "AdvancedEditorManager.h"
#include "DebugHeader.h"
#include "SlateBasics.h"
#include "AssetViewUtils.h"
#include "Animation/AnimCompositeBase.h"

void SAdvancedDeletionTab::Construct(const FArguments Args)
{
	bCanSupportFocus = {true};
	FSlateFontInfo TitleTextInfo = GetTextType();
	TitleTextInfo.Size = 12;

	//Store asset data passed into this widget.
	GetPackageAssetsArray = Args._SharedDataArray;

	//Create a slot to place objects
	ChildSlot
	[SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Asset List")))
			.Font(TitleTextInfo)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::White)
		]


		+ SVerticalBox::Slot()
		.VAlign(EVerticalAlignment::VAlign_Fill)
		[SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				/*SNew(SListView<TSharedPtr<FAssetData>>)
				.ItemHeight(24.0f)
				.ListItemsSource(&GetPackageAssetsArray)
				.OnGenerateRow(this, &SAdvancedDeletionTab::GenerateRowForList)*/
				ConstructViewListForAssets()
			]
		]

	];
}


TSharedRef<ITableRow> SAdvancedDeletionTab::GenerateRowForList(TSharedPtr<FAssetData> DataToDisplay,
                                                               const TSharedRef<STableViewBase>& OwnerTable)
{
	//This function creates horizontal rows of multi-boxes. 
	// DataToDisplay returns a shared pointer so, we can directly access it's contents.

	const FString ClassName = DataToDisplay->AssetClass.ToString();
	const FString NamedAssets = DataToDisplay->AssetName.ToString();
	//Construct a row of FAssetData. 
	TSharedRef<STableRow<TSharedPtr<FAssetData>>> ListRow = SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable).
		Padding(FMargin(3.0f))
		[


			SNew(SHorizontalBox)

			//First slot reserved for a checkbox widget. 
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Left)
			  .VAlign(VAlign_Fill)
			  .FillWidth(.09f)
			[
				ConstructCheckBox(DataToDisplay)
			]

			//Second slot is reserved for displaying asset class names.
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Left)
			  .VAlign(VAlign_Center)
			  .FillWidth(.2f)
			[SNew(STextBlock)
				.Text(FText::FromString(NamedAssets))
			]

			//Third slot reserved for displaying assets names.

			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Center)
			  .VAlign(VAlign_Fill)
			  .FillWidth(.5f)
			[
				//SNew(STextBlock).Text(FText::FromString(ClassName))
				//TODO. Create a function that controlls the text style. 
				ConstructTextRowForWidget(ClassName)

			]
			// The forth slot is reserved for controls.
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Right)
			  .VAlign(VAlign_Fill)
			  .FillWidth(.1)

			[
				ConstructButtonForWidget(DataToDisplay)
			]

		];

	return ListRow;
}
TSharedRef<SListView<TSharedPtr<FAssetData>>>SAdvancedDeletionTab::ConstructViewListForAssets()
{
	AssetListView = SNew(SListView<TSharedPtr<FAssetData>>) //This returns a TShared pointer.
	.ItemHeight(24.0f)
	.ListItemsSource(&GetPackageAssetsArray)
	.OnGenerateRow(this,&SAdvancedDeletionTab::GenerateRowForList);
	return AssetListView.ToSharedRef();
}

TSharedRef<SCheckBox> SAdvancedDeletionTab::ConstructCheckBox(const TSharedPtr<FAssetData>& DataToDisplay)
{
	TSharedRef<SCheckBox> ConstructCheckBox = SNew(SCheckBox)
		.Type(ESlateCheckBoxType::CheckBox)
	.OnCheckStateChanged(this, &SAdvancedDeletionTab::CheckBoxChangeState, DataToDisplay)
	.Visibility(EVisibility::Visible);
	return ConstructCheckBox;
}

void SAdvancedDeletionTab::CheckBoxChangeState(ECheckBoxState CurrentBoxSate, TSharedPtr<FAssetData> Data)
{
	switch (CurrentBoxSate)
	{
	case ECheckBoxState::Unchecked:

		Print(Data->AssetName.ToString() + TEXT(" is unchecked "), FColor::Red);
		break;
	case ECheckBoxState::Checked:
		Print(Data->AssetName.ToString() + TEXT(" is checked "), FColor::Green);
		break;
	case ECheckBoxState::Undetermined:

		break;
	default: ;
	}
}

TSharedRef<STextBlock> SAdvancedDeletionTab::ConstructTextRowForWidget(const FString& TextContent)
{
	FSlateFontInfo WidgetText = GetTextType();
	WidgetText.Size = 12.0f;

	TSharedRef<STextBlock> TextBlock = SNew(STextBlock).
	Text(FText::FromString(TextContent))
	.Font(WidgetText)
	.ColorAndOpacity(FColor::White);


	return TextBlock;
}

TSharedRef<SButton> SAdvancedDeletionTab::ConstructButtonForWidget(const TSharedPtr<FAssetData> Data)
{
	TSharedRef<SButton> NewButtonEvent = SNew(SButton)
	.Text(FText::FromString(TEXT("Delete")))
	.OnClicked(this, &SAdvancedDeletionTab::DeleteButtonClicked, Data);

	return NewButtonEvent;
}

FReply SAdvancedDeletionTab::DeleteButtonClicked(TSharedPtr<FAssetData> SelectedData)
{
	Print(SelectedData->AssetName.ToString() + TEXT("is being removed..."),FColor::Emerald);
	//Load a reference to the current Manager Module
	FAdvancedEditorManagerModule& AdvancedManagerModule = FModuleManager::LoadModuleChecked<
		FAdvancedEditorManagerModule>(TEXT("AdvancedEditorManager"));
	
	if (const bool AssetDeleted = AdvancedManagerModule.DeleteSingleAssetFromList(*SelectedData.Get()))
	{
		if(GetPackageAssetsArray.Contains(SelectedData))
			GetPackageAssetsArray.Remove(SelectedData);
		
	}
	RefreshListView();
	
	//This replay event needs to return another value. 

	return FReply::Handled();
}

void SAdvancedDeletionTab::RefreshListView()
{
	if(AssetListView.IsValid())
	{
		AssetListView->RebuildList();
	}
	
}
