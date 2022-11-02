// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetManager.h"

#include "AssetSelection.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "DebugHeader.h"
#include "Materials/MaterialInstanceConstant.h"


void UQuickAssetManager::DuplicateAssets(uint64 NumberOfDuplicates)
{
	//Set variable for safety reasons.
	//NumberOfDuplicates ={0};

	if (NumberOfDuplicates <= 0)
	{
		Print("Please Enter a Valid Number", FColor::Blue);


		ShowDialog(EAppMsgType::Ok,TEXT("Please enter a valid Number."));
		return;
	}


	// Create an AssetData array. 
	TArray<FAssetData> SelectedAssetData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 counter{0};
	// iterate through it.
	for (const FAssetData& AssetData : SelectedAssetData)
	{
		//iterate again to create a new file name and path location.
		for (uint32 i = 0; counter < NumberOfDuplicates; ++i)
		{
			const FString SourceAssetPath = AssetData.ObjectPath.ToString();
			const FString NewDuplicatedAssetName = AssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i);
			const FString NewPath = FPaths::Combine(AssetData.PackagePath.ToString(), NewDuplicatedAssetName);

			//check for valid path. if valid duplicate path and append a new name to each asset. 
			if (UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPath))
			{
				UEditorAssetLibrary::SaveAsset(NewPath, false);
				++counter;
				//Print(("%s",SelectedAssetData),FColor::Emerald);
			}
		}
		if (counter > 0)
		{
			//add debug message;
			ShowNotificationInfo("Successfully Duplicated " + FString::FromInt(counter) + " files.");
		}
	}
}

void UQuickAssetManager::RenamePrefix()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 counter =0;
	for(UObject* selectedobject: SelectedObjects)
	{
		if(!selectedobject)
		{
			continue;
		}
		FString* prefixfound = PrefixMap.Find(selectedobject->GetClass()); //The "Find" operation returns a pointer. 
		if(!prefixfound||prefixfound->IsEmpty())
		{
			Print(TEXT("Failed to find Prefix for Class.")+selectedobject->GetClass()->GetName(),FColor::Red);
			continue;
		}
		//create a name when object is right clicked. 
		FString oldname = selectedobject->GetName();
		if(oldname.StartsWith(*prefixfound))
		{
			Print(oldname+TEXT(" Already has prefix added."), FColor::Red);
			continue;
		}
		if(selectedobject->IsA<UMaterialInstanceConstant>())
		{
			//remove the prefix and suffix from a material instance. 
			oldname.RemoveFromStart(TEXT("M_"));
			oldname.RemoveFromEnd(TEXT("_Inst"));
		}
		const FString newname = *prefixfound + oldname;

		UEditorUtilityLibrary::RenameAsset(selectedobject,newname);
		++counter;
		
		
	}
	if(counter>0)
	{
		ShowNotificationInfo(TEXT("Successfully renamed " + FString::FromInt(counter)+ " Assets"));
	}

	//create an array to get selected assets
	//create another array to store the unused assets
	//loop through the assets that were found.
	//hint findpackagerefferences
	//store the elements in a temperary array
	//add the assets to the temp array
	//check assets if they are being used
	// print message if they are being used.
	//if we get past this check.
	//include header files objecttools.h to access better delete tools
	//delete assets. This action may need to include a module. 
}
