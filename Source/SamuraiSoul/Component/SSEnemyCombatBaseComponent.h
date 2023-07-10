// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/SSCombatComponent.h"
#include "SSEnemyCombatBaseComponent.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSEnemyCombatBaseComponent : public USSCombatComponent
{
	GENERATED_BODY()

public:
	USSEnemyCombatBaseComponent();

	virtual void BeginPlay() override;

	virtual void SetEnemyWeapon() const;
	virtual void AttackByAI() const;
	void SpecialAttackByAI(const FGameplayTag& AbilityTag) const;

	virtual void Rebound() override;

protected:
};
