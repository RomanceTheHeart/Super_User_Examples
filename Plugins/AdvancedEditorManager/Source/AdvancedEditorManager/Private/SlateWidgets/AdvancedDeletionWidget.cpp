// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvancedDeletionWidget.h"
#include "DebugHeader.h"
#include "SlateBasics.h"
#include "AssetViewUtils.h"
#include "Animation/AnimCompositeBase.h"

void SAdvancedDeletionTab::Construct(const FArguments Args)
{
	bCanSupportFocus = {true};
	FSlateFontInfo TitleTextInfo = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextInfo.Size = 14;

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
		//This second slot is used to specify the list condition along with help text.
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
		]
		//This third slot is used to list various asset.
		+ SVerticalBox::Slot()
		.VAlign(EVerticalAlignment::VAlign_Fill)
		[SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SNew(SListView<TSharedPtr<FAssetData>>)
				.ItemHeight(24.0f)
				.ListItemsSource(&GetPackageAssetsArray)
				.OnGenerateRow(this, &SAdvancedDeletionTab::GenerateRowForList)
			]
		]
		// This fourth slot is used to create three buttons.
		+ SVerticalBox::Slot()
		.AutoHeight()
		[SNew(SHorizontalBox)
		]
	];
}

TSharedRef<ITableRow> SAdvancedDeletionTab::GenerateRowForList(TSharedPtr<FAssetData> DataToDisplay,
                                                               const TSharedRef<STableViewBase>& OwnerTable)
{
	//This function creates horizontal rows of multiboxes. 
	// DataToDisplay returns a shared pointer so, we can directly access it's contents.

	const FString ClassName = DataToDisplay->AssetClass.ToString();
	const FString NamedAssets = DataToDisplay->AssetName.ToString();
	//Construct a row of FAssetData. 
	TSharedRef<STableRow<TSharedPtr<FAssetData>>> ListRow = SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable).Padding(FMargin(3.0f))
	[


		SNew(SHorizontalBox)

		//First slot reserved for a checkbox widget. 
		+ SHorizontalBox::Slot()
		  .HAlign(HAlign_Left)
		  .VAlign(VAlign_Fill)
		  .FillWidth(.1f)
		[
			ConstructCheckBox(DataToDisplay)
		]

		//Second slot is reserved for displaying asset class names.
		+ SHorizontalBox::Slot()
		  .HAlign(HAlign_Left)
		  .VAlign(VAlign_Center)
		  .FillWidth(.1f)
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
			ConstructTextRowForWidget(ClassName)

		]
		// The forth slot is reserved for controls. 

	];

	return ListRow;
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
