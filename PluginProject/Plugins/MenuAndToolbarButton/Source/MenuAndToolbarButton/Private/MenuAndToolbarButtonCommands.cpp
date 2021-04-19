// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuAndToolbarButtonCommands.h"

#define LOCTEXT_NAMESPACE "FMenuAndToolbarButtonModule"

void FMenuAndToolbarButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MenuAndToolbarButton", "Execute MenuAndToolbarButton action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
