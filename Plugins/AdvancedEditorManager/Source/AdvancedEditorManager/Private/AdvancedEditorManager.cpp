// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedEditorManager.h"
#include "ContentBrowserModule.h"

#define LOCTEXT_NAMESPACE "FAdvancedEditorManagerModule"

void FAdvancedEditorManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAdvancedEditorManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
#pragma region MenuExtention

void FAdvancedEditorManagerModule::Init_MenuExtention()
{
	FContentBrowserModule& BrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(
		TEXT("ContentBrowser"));
	TArray<FContentBrowserMenuExtender_SelectedPaths>& BrowserModuleMenuExtenders = BrowserModule.
		GetAllPathViewContextMenuExtenders();
	FContentBrowserMenuExtender_SelectedPaths CustomMenuDelegats;
	BrowserModuleMenuExtenders.Add(CustomMenuDelegats);
}
#pragma endregion

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdvancedEditorManagerModule, AdvancedEditorManager)
