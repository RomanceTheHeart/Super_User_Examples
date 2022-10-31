// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetManager.h"

#include "AssetSelection.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "DebugHeader.h"
#include "Algo/Count.h"


void UQuickAssetManager::DuplicateAssets(uint64 NumberOfDuplicates)
{
	

	if (NumberOfDuplicates < 0)
	{
		//Print("Please Enter a Valid Number",FColor::Blue);

		
		ShowDialog(EAppMsgType::Ok,TEXT("Please enter a valid Number."));
		return;
	}	

	// Create an AssetData array. 
	TArray<FAssetData> SelectedAssetData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 counter{0};
	// iterate through it.
	for(const FAssetData& AssetData:SelectedAssetData)
	{
		 //iterate again to create a new file name and path location.
		for(uint32 i=0; counter < NumberOfDuplicates; ++i)
		{
			
			const FString SourceAssetPath = AssetData.ObjectPath.ToString();
			const FString NewDuplicatedAssetName = AssetData.AssetName.ToString() + TEXT("_")+ FString::FromInt(i);
			const FString NewPath = FPaths::Combine(AssetData.PackagePath.ToString(),NewDuplicatedAssetName);

			//check for valid path. if valid duplicate path and append a new name to each asset. 
			if(UEditorAssetLibrary::DuplicateAsset(SourceAssetPath,NewPath))
			{
				
				UEditorAssetLibrary::SaveAsset(NewPath,false);
				++counter;
				//Print(("%s",SelectedAssetData),FColor::Emerald);
				
			}
			
			
		}
		if(counter>0)
		{
			//add debug message;
			ShowNotificationInfo("Successfully Duplicated " + FString::FromInt(counter) + " files.");
		}
	
	}
	
	
}
