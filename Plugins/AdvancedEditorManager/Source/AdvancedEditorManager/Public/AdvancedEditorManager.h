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
	TArray<FString> FolderAssetLocations = {"/Game"};

	uint32 NumberAssets = {0};
	void Init_MenuExtention();
	TSharedRef<FExtender> CustomContentExtender(const TArray<FString>& SelectedPaths);
	void AddCustomContentEntry(class FMenuBuilder& MenuBuilder);
	void OnDeleteUnusedAssets();
	void FixRedirectors();


#pragma endregion


#pragma region NomadTab
	void RegisterAdvancedDeletion_Protocol();
	TSharedRef<SDockTab> SpawnDeletionTab(const FSpawnTabArgs& spawner);
	void AdvancedDelete();

	TArray<TSharedPtr<FAssetData>> ReturnPackageAssets();
#pragma endregion

public:
#pragma region ProccessAdvancedDeletionWidget

	bool DeleteSingleAssetFromList(const FAssetData& DataToDelete);
#pragma endregion
};
