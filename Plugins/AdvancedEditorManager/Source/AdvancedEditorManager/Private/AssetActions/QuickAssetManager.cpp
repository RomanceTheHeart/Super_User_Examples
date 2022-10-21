// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetManager.h"



void UQuickAssetManager::TestFunction()
{
	
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,30.0,FColor::Black,TEXT("This Works!"));
	}
}
