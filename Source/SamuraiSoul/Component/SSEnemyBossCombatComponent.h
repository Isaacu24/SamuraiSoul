// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/SSEnemyCombatBaseComponent.h"
#include "SSEnemyBossCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSEnemyBossCombatComponent : public USSEnemyCombatBaseComponent
{
	GENERATED_BODY()

public:
	USSEnemyBossCombatComponent();

	virtual void BeginPlay() override;

protected:
	virtual void Hit(EAttackType InType) override;

protected:
};
