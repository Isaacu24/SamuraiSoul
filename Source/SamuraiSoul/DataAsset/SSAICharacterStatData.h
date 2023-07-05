// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SSAICharacterStatData.generated.h"

/**
 *
 */
UCLASS()
class SAMURAISOUL_API USSAICharacterStatData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	USSAICharacterStatData();

	UPROPERTY(EditAnywhere, Category = Stat)
	float AIAttackRange;

	UPROPERTY(EditAnywhere, Category = Stat)
	float AIPatrolRadius;

	UPROPERTY(EditAnywhere, Category = Stat)
	float AIDetectRadius;

	UPROPERTY(EditAnywhere, Category = Stat)
	float AILoseDetectRadius;

	UPROPERTY(EditAnywhere, Category = Stat)
	float AISight;

	UPROPERTY(EditAnywhere, Category = Stat)
	float AIHearingRange;

	UPROPERTY(EditAnywhere, Category = Enemy)
	int AIMaxAttackCount;

	UPROPERTY(EditAnywhere, Category = Enemy)
	FGameplayTag SpectialAttackTag;
};
