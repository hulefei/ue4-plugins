# 添加菜单和工具栏

> UE4 Plugin 添加菜单和工具栏有两种方式：FExtender方式 和 UToolMenus方式

## FExtender方式

### 添加工具栏

```cpp
TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
MenuExtender->AddToolBarExtension(ExtensionHook, EExtensionHook::After, PluginCommands,
//在AddDataTableEditorToolBarExtension 中设置SectionName
FToolBarExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddToolBarExtension));
EditorModule.GetToolBarExtensibilityManager()->AddExtender(MenuExtender);
```
### 添加在已有菜单

```cpp
TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
MenuExtender->AddMenuExtension(ExtensionHook, EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddMenuExtension));
EditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
```
### 添加在菜单栏

```cpp
TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
MenuExtender->AddMenuBarExtension(ExtensionHook, EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FMenuAndToolbarButtonModule::AddMenuBarExtension));
EditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
```

### EditorModule

#### FLevelEditorModule

```cpp
FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
```

#### FLevelEditorModule

```cpp
FDataTableEditorModule& DataTableEditorModule = FModuleManager::LoadModuleChecked<FDataTableEditorModule>("DataTableEditor");
```

#### FLevelEditorModule

```cpp
FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("BlueprintEditor");
```

## UToolMenus方式

### 添加菜单

```cpp
UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu(InName);
{
	FToolMenuSection& Section = ToolMenu->FindOrAddSection(SectionName);
	Section.AddMenuEntryWithCommandList(FMenuAndToolbarButtonCommands::Get().PluginAction, PluginCommands);
}
```

### 添加工具栏

```cpp
UToolMenu* ToolMenu = UToolMenus::Get()->ExtendMenu(InName);
{
	//添加工具栏
	FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMenuAndToolbarButtonCommands::Get().PluginAction));
	Entry.SetCommandList(PluginCommands);

}
```

### InName

#### LevelEditor

* LevelEditor.LevelEditorToolBar
* LevelEditor.MainMenu

#### AssetEditor

* AssetEditor.BlueprintEditor.ToolBar
* AssetEditor.BlueprintEditor.MainMenu
* AssetEditor.DataTableEditor.ToolBar
* AssetEditor.DataTableEditor.MainMenu

...


## 代码

https://github.com/hulefei/ue4-plugins/tree/main/PluginProject/Plugins/MenuAndToolbarButton