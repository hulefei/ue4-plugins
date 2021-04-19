// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuAndToolbarButton.h"


#include "BlueprintEditorModule.h"
#include "DataTableEditorModule.h"
#include "LevelEditor.h"
#include "MenuAndToolbarButtonStyle.h"
#include "MenuAndToolbarButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName MenuAndToolbarButtonTabName("MenuAndToolbarButton");

#define LOCTEXT_NAMESPACE "FMenuAndToolbarButtonModule"

void FMenuAndToolbarButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMenuAndToolbarButtonStyle::Initialize();
	FMenuAndToolbarButtonStyle::ReloadTextures();

	FMenuAndToolbarButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMenuAndToolbarButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMenuAndToolbarButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::RegisterMenus));
}

void FMenuAndToolbarButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMenuAndToolbarButtonStyle::Shutdown();

	FMenuAndToolbarButtonCommands::Unregister();
}

void FMenuAndToolbarButtonModule::AddMenuBarExtension(FMenuBarBuilder& Builder)
{
	Builder.AddMenuEntry(FMenuAndToolbarButtonCommands::Get().PluginAction);
}

void FMenuAndToolbarButtonModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMenuAndToolbarButtonCommands::Get().PluginAction);
}

void FMenuAndToolbarButtonModule::AddToolBarExtension(FToolBarBuilder& Builder)
{
	FName SectionName = FName(TEXT("FExtenderWay"));
	Builder.BeginSection(SectionName);
	Builder.AddToolBarButton(FMenuAndToolbarButtonCommands::Get().PluginAction);
	Builder.EndSection();
}

void FMenuAndToolbarButtonModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FMenuAndToolbarButtonModule::PluginButtonClicked()")),
							FText::FromString(TEXT("MenuAndToolbarButton.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FMenuAndToolbarButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	// 1. UToolMenu方式：使用简单，自定义能力弱
	//A.添加在工具栏的末尾
	ExtendMenuAndToolbarByUToolMenu(false, FName("LevelEditor.LevelEditorToolBar"), FName("ToolMenuWay"));
	//B.添加在已有菜单中
	ExtendMenuAndToolbarByUToolMenu(true, FName("LevelEditor.MainMenu.Help"), FName("HelpApplication"));
	//C.添加在菜单栏
	//添加新的menu时，FMenuAndToolbarButtonCommands 中的数据
	ExtendMenuAndToolbarByUToolMenu(true, FName("LevelEditor.MainMenu"), FName("ToolMenuWay"));
	//A.添加在已有菜单中
	ExtendMenuAndToolbarByUToolMenu(true, FName("LevelEditor.MainMenu.PluginAction"), FName("ToolMenuWay"));

	//2. FExtend方式
	//A.添加在工具栏的末尾
	ExtendMenuAndToolbarByFExtender(1, FName("File"), FName());
	//B.添加在已有菜单中
	ExtendMenuAndToolbarByFExtender(2, FName("HelpApplication"), FName());
	//C.添加在菜单栏
	ExtendMenuAndToolbarByFExtender(3, FName("Help"), FName());


	//其他Editor
	ExtendMenuAndToolbarByUToolMenu(false, FName("AssetEditor.BlueprintEditor.ToolBar"), FName("ToolMenuWay"));
	ExtendMenuAndToolbarByUToolMenu(true, FName("AssetEditor.BlueprintEditor.MainMenu.Help"), FName("HelpApplication"));
	ExtendMenuAndToolbarByUToolMenu(true, FName("AssetEditor.BlueprintEditor.MainMenu"), FName("ToolMenuWay"));
	ExtendMenuAndToolbarByUToolMenu(true, FName("AssetEditor.BlueprintEditor.MainMenu.PluginAction"), FName("ToolMenuWay"));

	ExtendDataTableMenuAndToolbarByFExtender(1, FName("DataTableCommands"));
	ExtendDataTableMenuAndToolbarByFExtender(2, FName("HelpApplication"));
	ExtendDataTableMenuAndToolbarByFExtender(3, FName("Help"));
}

void FMenuAndToolbarButtonModule::ExtendMenuAndToolbarByFExtender(int Type, FName ExtensionHook, FName EditorName)
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	if (Type == 1)
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddToolBarExtension(ExtensionHook,
               EExtensionHook::After, PluginCommands,
               //在AddDataTableEditorToolBarExtension 中设置SectionName
               FToolBarExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddToolBarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(MenuExtender);
	} else if (Type == 2)
	{
		//B.添加在已有菜单
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuExtension(ExtensionHook,
                    EExtensionHook::After, PluginCommands,
                  FMenuExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddMenuExtension));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	} else
	{
		// C.添加在菜单栏
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(ExtensionHook,
                    EExtensionHook::After, PluginCommands,
                  FMenuBarExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddMenuBarExtension));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
}

void FMenuAndToolbarButtonModule::ExtendMenuAndToolbarByUToolMenu(bool IsMenu, FName InName, FName SectionName)
{
	{
		UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu(InName);
		{
			FToolMenuSection& Section = ToolMenu->FindOrAddSection(SectionName);

			if (IsMenu)
			{
				//添加菜单
				Section.AddMenuEntryWithCommandList(FMenuAndToolbarButtonCommands::Get().PluginAction, PluginCommands);
			} else
			{
				//添加工具栏
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMenuAndToolbarButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

//其他Editor
void FMenuAndToolbarButtonModule::ExtendDataTableMenuAndToolbarByFExtender(int Type, FName ExtensionHook)
{
	FDataTableEditorModule& DataTableEditorModule = FModuleManager::LoadModuleChecked<FDataTableEditorModule>("DataTableEditor");
	if (Type == 1)
	{
		//A: 添加工具栏
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddToolBarExtension(ExtensionHook,
               EExtensionHook::After, PluginCommands,
               //在AddDataTableEditorToolBarExtension 中设置SectionName
               FToolBarExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddToolBarExtension));
		DataTableEditorModule.GetToolBarExtensibilityManager()->AddExtender(MenuExtender);
	} else if (Type == 2)
	{
		//B.添加在已有菜单
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuExtension(ExtensionHook,
                    EExtensionHook::After, PluginCommands,
                  FMenuExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddMenuExtension));
		DataTableEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	} else
	{
		// C.添加在菜单栏
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(ExtensionHook,
                    EExtensionHook::After, PluginCommands,
                  FMenuBarExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddMenuBarExtension));
		DataTableEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMenuAndToolbarButtonModule, MenuAndToolbarButton)