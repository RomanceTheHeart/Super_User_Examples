// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvancedDeletionWidget.h"
#include "SlateBasics.h"

#include "AssetViewUtils.h"

void SAdvancedDeletionTab::Construct(const FArguments Args)
{
	bCanSupportFocus = {true};
	FSlateFontInfo TitleTextInfo = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextInfo.Size = 15;

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
                                                               const TSharedRef<STableViewBase>& OwnerTable) const
{
	//This function returns list of tsharedrefferences to sharedptr fasset data. 
	// DataToDisplay returns a shared pointer so, we can directly access it's contents.
	// This one is tricky. Needs more attention. 
	const FString NamedAssets = DataToDisplay->AssetName.ToString();
	//this returns a whole row of assets.
	TSharedRef<STableRow<TSharedPtr<FAssetData>>> ListRow = SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable)
	[

	
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		  .HAlign(HAlign_Left)
		  .VAlign(VAlign_Center)
		  .FillWidth(.5f)
		  [
		  	ConstructCheckBox(DataToDisplay)
		  	]

		  	
		  	+SHorizontalBox::Slot()
		  	[		SNew(STextBlock)
		.Text(FText::FromString(NamedAssets))
		  		]

	];

	return ListRow;
}

TSharedRef<SCheckBox> SAdvancedDeletionTab::ConstructCheckBox(const TSharedPtr<FAssetData>& DataToDisplay) const
{
	TSharedRef<SCheckBox> ConstructCheckBox = SNew(SCheckBox)
		.Type(ESlateCheckBoxType::CheckBox);
	return ConstructCheckBox;
}
