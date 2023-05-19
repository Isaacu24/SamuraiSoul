// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "../Interface/SSCombatInterface.h"
#include "../Interface/SSCharacterAIInterface.h"
#include "SSEnemyCharacterBase.generated.h"

class USSEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyCharacterBase : public ASSCharacterBase, public ISSCharacterAIInterface, public ISSCombatInterface
{
	GENERATED_BODY()

public:
	ASSEnemyCharacterBase();

protected:
	virtual USSCombatComponent* GetCombatComponent() const override
	{
		return static_cast<USSCombatComponent*>(CombatComponent);
	}

	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

protected:
	FAICharacterAttackFinished OnAttackFinished;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSEnemyCombatComponent> CombatComponent;
};
