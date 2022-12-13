// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "QuickAssetManager.generated.h"


/**
 * 
 */
class UBlueprint;
UCLASS()
class ADVANCEDEDITORMANAGER_API UQuickAssetManager : public UAssetActionUtility
{
	GENERATED_BODY()
private:
	TMap<UClass*,FString>PrefixMap =
		{
		{UBlueprint::StaticClass(),TEXT("BP_")},
	};

	public: 
	UFUNCTION(CallInEditor)
	void DuplicateAssets(uint64 NumberOfDuplicates);

	UFUNCTION(CallInEditor)
	void RenamePrefix();

	//Create a function
	//deleteunsedassets()
	UFUNCTION(CallInEditor)
	void DeleteUnusedAssets();
	
	
};
