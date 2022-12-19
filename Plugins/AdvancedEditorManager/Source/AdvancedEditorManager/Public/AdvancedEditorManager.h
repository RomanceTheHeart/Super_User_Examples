// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAdvancedEditorManagerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


#pragma region MenuExtention
private:
	TArray<FString>FolderAssetLocations;
	uint32 NumberAssets = {0};
	void Init_MenuExtention();
	TSharedRef<FExtender> CustomContentExtender(const TArray<FString>& SelectedPaths);
	void AddCustomContentEntry(class FMenuBuilder& MenuBuilder);
	void OnDeleteUnusedAssets();

#pragma endregion
};
