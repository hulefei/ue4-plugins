// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMenuAndToolbarButtonModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void AddToolBarExtension(FToolBarBuilder& Builder);
	void AddMenuBarExtension(FMenuBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	void ExtendMenuAndToolbarByUToolMenu(bool IsMenu, FName InName, FName SectionName);
	void ExtendMenuAndToolbarByFExtender(int Type, FName ExtensionHook, FName EditorName);

	void ExtendDataTableMenuAndToolbarByFExtender(int Type, FName ExtensionHook);
private:

	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
