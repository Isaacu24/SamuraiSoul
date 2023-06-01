// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SSCharacterData.generated.h"

class USSAbilitySet;

/**
 * 
 */
UCLASS(BlueprintType)
class SAMURAISOUL_API USSCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	USSCharacterData();

	UPROPERTY(EditAnywhere, Category = Ability)
	TObjectPtr<USSAbilitySet> AbilitySet;
};
