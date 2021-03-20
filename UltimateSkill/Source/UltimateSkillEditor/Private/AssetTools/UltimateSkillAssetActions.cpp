// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateSkillAssetActions.h"

#include "UltimateSkillAsset.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

FUltimateSkillAssetActions::FUltimateSkillAssetActions()
{
}

uint32 FUltimateSkillAssetActions::GetCategories()
{
	return EAssetTypeCategories::Basic;
}

FText FUltimateSkillAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_UltimateSkillAsset", "Ultimate Skill Asset");
}

UClass* FUltimateSkillAssetActions::GetSupportedClass() const
{
	return UUltimateSkillAsset::StaticClass();
}

FColor FUltimateSkillAssetActions::GetTypeColor() const
{
	return FColor::Blue;
}

void FUltimateSkillAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
	
	const auto NextAnimAssets = GetTypedWeakObjectPtrs<UUltimateSkillAsset>(InObjects);
	
	MenuBuilder.AddMenuEntry(
		LOCTEXT("NextAnimAsset_UltimateSkill", "Ultimate Skill"),
		LOCTEXT("NextAnimAsset_UltimateSkillTip", "Ultimate Skill Tip"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=]
			{
				//TODO
				// const FText DialogText = LOCTEXT("TODO", "待实现");
				// FMessageDialog::Open(EAppMsgType::Ok, DialogText);
			}),
			FCanExecuteAction::CreateLambda([=]
			{
				return true;
			})
		)
	);
}

bool FUltimateSkillAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

#undef LOCTEXT_NAMESPACE