// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedEditorManager.h"
#include "ContentBrowserModule.h"

#define LOCTEXT_NAMESPACE "FAdvancedEditorManagerModule"

void FAdvancedEditorManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	Init_MenuExtention();
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
}

void FAdvancedEditorManagerModule::OnDeleteUnusedAssets()
{
}


#pragma endregion

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdvancedEditorManagerModule, AdvancedEditorManager)
