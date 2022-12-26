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
			.Text(FText::FromString(TEXT("Advanced Deletion")))
			.Font(TitleTextInfo)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::White)
		]
		//This second slot is used to specify the list condition along with help text.
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SVerticalBox)
		]
		//This third slot is used to list various asset.
		+ SVerticalBox::Slot()
		.AutoHeight()
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
	// DataToDisplay returns a shared pointer so, we can directly access it's contents. 
	const FString NamedAssets = DataToDisplay->AssetName.ToString();
	TSharedRef<STableRow<TSharedPtr<FAssetData>>> ListRow = SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable)
	[
		SNew(STextBlock)
		.Text(FText::FromString(NamedAssets))
	];

	return ListRow;
}
