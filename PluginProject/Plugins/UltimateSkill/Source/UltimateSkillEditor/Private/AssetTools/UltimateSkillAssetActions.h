// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class ULTIMATESKILLEDITOR_API FUltimateSkillAssetActions : public FAssetTypeActions_Base
{
public:
	FUltimateSkillAssetActions();
	// void CreateBlueprint();

	public:
	//~ FAssetTypeActions_Base overrides
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual  UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;

	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;

	private:
	// virtual bool AddMenuEntryForType(FMenuBuilder& MenuBuilder, FString TypeName, TArray<TWeakObjectPtr<class UUltimateSkillAsset>> UltimateSkillAssets) const;
};
