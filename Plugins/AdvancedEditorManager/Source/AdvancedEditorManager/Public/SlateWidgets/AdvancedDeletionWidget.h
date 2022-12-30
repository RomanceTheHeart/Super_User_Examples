// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Widgets/SCompoundWidget.h"
//the basics of slate widgets
// we need to pass in some macros - study the definition. 
// create a construction function.
class SAdvancedDeletionTab : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAdvancedDeletionTab)
		{
		}

		SLATE_ARGUMENT(FString, TitleString)

		//Create a list that will be passed onto the slatewidget.
		SLATE_ARGUMENT(TArray<TSharedPtr<FAssetData>>, SharedDataArray)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments Args);
private:
		FSlateFontInfo GetTextType(){return   FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));}
	//This will be where more functions to organise the code will be housed.
	//Data will be passed into this array from the AdvancedManager.
	TArray<TSharedPtr<FAssetData>> GetPackageAssetsArray;

	//This delegate function is used to passed data to the widget.
	TSharedRef<ITableRow> GenerateRowForList(TSharedPtr<FAssetData> DataToDisplay
	                                         , const TSharedRef<STableViewBase>& OwnerTable);

	TSharedRef<SCheckBox> ConstructCheckBox(const TSharedPtr<FAssetData>& DataToDisplay);

	//CheckBoxStateChanged true/false
	void CheckBoxChangeState(ECheckBoxState CurrentBoxSate, TSharedPtr<FAssetData> Data);

	TSharedRef<STextBlock> ConstructTextRowForWidget(const FString& TextContent);

	TSharedRef<SButton>ConstructButtonForWidget(const TSharedPtr<FAssetData> Data);
	FReply DeleteButtonClicked(TSharedPtr<FAssetData>SelectedData);
};
