// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateSkillFactoryNew.h"
#include "UltimateSkillAsset.h"

UUltimateSkillFactoryNew::UUltimateSkillFactoryNew(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	SupportedClass = UUltimateSkillAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


UObject* UUltimateSkillFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UUltimateSkillAsset>(InParent, InClass, InName, Flags);
}

bool UUltimateSkillFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
