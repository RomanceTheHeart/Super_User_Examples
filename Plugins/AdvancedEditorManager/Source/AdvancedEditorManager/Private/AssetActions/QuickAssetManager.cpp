// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetManager.h"

#include "AssetSelection.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "DebugHeader.h"
#include "Components/DecalComponent.h"


void UQuickAssetManager::DubplicateAssets(int32 NumberOfDuplicates)
{
	

	if (NumberOfDuplicates < 0)
	{
		Print("Please Enter a Valid Number",FColor::Blue);
		return;
	}	

	// Create an AssetData array. 
	TArray<FAssetData> SelectedAssetData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 counter{0};
	// iterate through it.
	for(const FAssetData& AssetData:SelectedAssetData)
	{
		 //iterate again to create a new file name and path location.
		for(int32 i=0; NumberOfDuplicates; i++)
		{
			
			const FString SourceAssetPath = AssetData.ObjectPath.ToString();
			const FString NewDuplicatedAssetName = AssetData.AssetName.ToString() + TEXT("_")+ FString::FromInt(i);
			const FString NewPath = FPaths::Combine(AssetData.PackagePath.ToString(),NewDuplicatedAssetName);

			//check for valid path. if valid duplicate path and append a new name to each asset. 
			if(UEditorAssetLibrary::DuplicateAsset(SourceAssetPath,NewPath))
			{
				
				UEditorAssetLibrary::SaveAsset(NewPath,false);
				//Print(("%s",SelectedAssetData),FColor::Emerald);
				
			}
			break;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *SourceAssetPath);
		}
	}
	
	
}
