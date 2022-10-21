// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "QuickAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDEDITORMANAGER_API UQuickAssetManager : public UAssetActionUtility
{
	GENERATED_BODY()

	public: 
	UFUNCTION(CallInEditor)
	void TestFunction();
	
};
