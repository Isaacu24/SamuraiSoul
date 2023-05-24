// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "Interface/SSCombatInterface.h"
#include "Interface/SSCharacterAIInterface.h"
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

	FAICharacterAbilityFinished OnAttackFinished;
	FAICharacterAbilityFinished OnExecutedFinished;

protected:
	virtual USSCombatComponent* GetCombatComponent() const override
	{
		return static_cast<USSCombatComponent*>(CombatComponent);
	}


	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAISight() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void Run() override;
	virtual void Walk() override;

	virtual void SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;
	virtual void AttackEnd() override;

	virtual void RunBehaviorTree() const override;
	virtual void StopBehaviorTree() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSEnemyCombatComponent> CombatComponent;
};
