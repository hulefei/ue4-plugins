// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "UltimateSkillAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ULTIMATESKILL_API UUltimateSkillAsset : public UObject
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=NewAsset)
	int Value;
};
