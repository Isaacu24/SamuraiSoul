// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "../Interface/SSCharacterAIInterface.h"
#include "SSEnemyCharacterBase.generated.h"

class USSCombatComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyCharacterBase : public ASSCharacterBase, public ISSCharacterAIInterface
{
	GENERATED_BODY()

public:
	ASSEnemyCharacterBase();

protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;
};
