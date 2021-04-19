// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MenuAndToolbarButtonStyle.h"

class FMenuAndToolbarButtonCommands : public TCommands<FMenuAndToolbarButtonCommands>
{
public:

	FMenuAndToolbarButtonCommands()
		: TCommands<FMenuAndToolbarButtonCommands>(TEXT("MenuAndToolbarButton"), NSLOCTEXT("Contexts", "MenuAndToolbarButton", "MenuAndToolbarButton Plugin"), NAME_None, FMenuAndToolbarButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
