// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedEditorManager.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"


#define LOCTEXT_NAMESPACE "FAdvancedEditorManagerModule"

void FAdvancedEditorManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	Init_MenuExtention();
	//Register the Nomad Tab. 
	RegisterAdvancedDeletion_Protocol();
}

void FAdvancedEditorManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
#pragma region MenuExtention

void FAdvancedEditorManagerModule::Init_MenuExtention()
{
	//Create an FContentBrowserModule Object.
	FContentBrowserModule& BrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(
		TEXT("ContentBrowser"));

	//Create an array that gets all of the selected menu paths.
	TArray<FContentBrowserMenuExtender_SelectedPaths>& BrowserModuleMenuExtenders = BrowserModule.
		GetAllPathViewContextMenuExtenders();


	//Create a FContentBroweserMenuExtender_SelectedPaths variable. 
	FContentBrowserMenuExtender_SelectedPaths CustomMenuDelegats;
	//Add this variable to the array of Browser Module Menu Extenders
	BrowserModuleMenuExtenders.Add(CustomMenuDelegats);

	//create a raw pointer delegate to assume responsibility for executing MenuExtenderFunction.
	BrowserModuleMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::
		CreateRaw(this, &FAdvancedEditorManagerModule::CustomContentExtender));
}

TSharedRef<FExtender> FAdvancedEditorManagerModule::CustomContentExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());
	if (SelectedPaths.Num() > 0)
	{
		MenuExtender->AddMenuExtension(FName("Delete"),
		                               EExtensionHook::After, TSharedPtr<FUICommandList>(),
		                               FMenuExtensionDelegate::CreateRaw(
			                               this, &FAdvancedEditorManagerModule::AddCustomContentEntry));
	}
	return MenuExtender;
}

void FAdvancedEditorManagerModule::AddCustomContentEntry(FMenuBuilder& MenuBuilder)
{
	//Build a menu entry. 
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Delete Unsed Assets")),
	                         FText::FromString(TEXT("Safely Delete Unused assets from selected folder.")),
	                         FSlateIcon(), FExecuteAction::
	                         CreateRaw(this, &FAdvancedEditorManagerModule::OnDeleteUnusedAssets));
	
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Advanced Deletion")),
							 FText::FromString(TEXT("An Advanced Way To Access Assets and Delete Them.")),
							 FSlateIcon(), FExecuteAction::
							 CreateRaw(this,&FAdvancedEditorManagerModule::AdvancedDelete));
}

void FAdvancedEditorManagerModule::OnDeleteUnusedAssets()
{
	Print("Deleting Assets", FColor::Green);

	//Before deleting asset folders fix-up the redirects. 
	FixRedirectors();

	FolderAssetLocations = {"/Game"};
	const TArray<FString>& FolderAssetPaths = UEditorAssetLibrary::ListAssets(FolderAssetLocations[0], true, true);

	Print(TEXT("Number of Assets: " + FString::FromInt(FolderAssetPaths.Num())), FColor::Green);

	FString EmptyFolderPath;
	TArray<FString> EmptyFolderPathArray;
	for (const FString& assetPath : FolderAssetPaths)
	{
		if (assetPath.Contains(TEXT("Developers")) ||
			assetPath.Contains(TEXT("Collections")) ||
			assetPath.Contains(TEXT("__ExternalActors__"))
			|| assetPath.Contains(TEXT("__ExternalObjects__")))
		{
			continue;
		}
		if (!UEditorAssetLibrary::DoesDirectoryExist(assetPath)) continue;
		if (!UEditorAssetLibrary::DoesDirectoryHaveAssets(assetPath))
		{
			EmptyFolderPath.Append(assetPath);
			EmptyFolderPath.Append("\n");
			EmptyFolderPathArray.Add(assetPath);
		}
	}

	//stepping out of the loop
	if (EmptyFolderPathArray.Num() == 0)
	{
		//Message is not a warning.
		Debug::ShowDialog(EAppMsgType::Ok,TEXT("No Empty Folders To Delete."), false);
		return;
	}
	EAppReturnType::Type Result = Debug::ShowDialog(EAppMsgType::OkCancel,
	                                                TEXT("Empty Folders Found in: " + EmptyFolderPath + TEXT(
		                                                " Would You Like to Delete All?")), false);

	if (Result == EAppReturnType::Cancel) return;

	for (FString& emptyfolders : EmptyFolderPathArray)
	{
		UEditorAssetLibrary::DeleteDirectory(emptyfolders)
			? ++NumberAssets
			: Debug::ShowDialog(EAppMsgType::Ok, "Failed To Delete Assets In: " + emptyfolders, false);
	}
	if (NumberAssets > 0)
	{
		Debug::ShowNotificationInfo("Successfully Deleted " + FString::FromInt(NumberAssets) + "Folders.");
	}
}

void FAdvancedEditorManagerModule::FixRedirectors()
{
	TArray<UObjectRedirector*> Fixes;
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(
		TEXT("AssetRegistry"));
	FARFilter RegisterFilter;
	RegisterFilter.bRecursivePaths = true;
	RegisterFilter.PackagePaths.Emplace("/Game");
	RegisterFilter.ClassNames.Emplace("ObjectRedirector");

	TArray<FAssetData> RedirectAssetData;
	AssetRegistryModule.Get().GetAssets(RegisterFilter, RedirectAssetData);

	for (const FAssetData& AssetData : RedirectAssetData)
	{
		if (UObjectRedirector* Redirection = Cast<UObjectRedirector>(AssetData.GetAsset()))
		{
			Fixes.Add(Redirection);
		}
	}
	const FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<
		FAssetToolsModule>(TEXT("AssetTools"));
	AssetToolsModule.Get().FixupReferencers(Fixes);
}


#pragma endregion

#pragma region NomadTab
void FAdvancedEditorManagerModule::RegisterAdvancedDeletion_Protocol()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("AdvancedDeletion"),
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FAdvancedEditorManagerModule::SpawnDeletionTab));
}

TSharedRef<SDockTab> FAdvancedEditorManagerModule::SpawnDeletionTab(const FSpawnTabArgs& spawner)
{
	
	return SNew(SDockTab).TabRole(ETabRole::NomadTab);
}

void FAdvancedEditorManagerModule::AdvancedDelete()
{
	//Print(TEXT("This Works!"),FColor::Blue);
	FGlobalTabmanager::Get()->TryInvokeTab(FName("AdvancedDeletion"));
}
#pragma endregion

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdvancedEditorManagerModule, AdvancedEditorManager)
