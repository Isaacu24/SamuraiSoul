// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "Interface/SSCombatableInterface.h"
#include "Interface/SSTargetableInterface.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSEnemyCharacterBase.generated.h"


class USSWidgetComponent;
class USSAICharacterStatData;
class USSEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyCharacterBase : public ASSCharacterBase, public ISSTargetableInterface, public ISSCharacterAIInterface,
                                              public ISSCombatableInterface
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

	virtual void BeginPlay() override;

	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRadius() override;
	virtual float GetAILoseDetectRadius() override;
	virtual float GetAISight() override;
	virtual float GetAIAttackRange() override;

	virtual uint8 GetCurrentCombo()
	{
		if (3 <= CurrentCombo)
		{
			CurrentCombo = 0;
		}

		++CurrentCombo;

		return CurrentCombo;
	}

	virtual void StopAI() override;
	virtual void RunAI() override;

	virtual void Run() override;
	virtual void Walk() override;

	virtual void SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;
	virtual void SpectialAttackByAI(const FGameplayTag& Tag) override;
	virtual void AttackEnd() override;

	virtual void EquipUnarm() override;

	virtual void ShowPerilousMark() override;
	virtual void HidePerilousMark() override;

	virtual void SetParry(bool Value) override;

	virtual void SetHit(bool Value) override;
	virtual void SetDead(bool Value) override;
	virtual void SetRebound(bool Value) override;
	virtual void SetEquip(bool Value) override;
	virtual void SetBeExecuted(bool Value) override;

	virtual FTargetingEndedDelegate& GetTargetingEndedDelegate() override;

	virtual void Die() override;

	virtual void VisibleTargetUI() override;
	virtual void HideTargetUI() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSEnemyCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSWidgetComponent> PerilousMark;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSWidgetComponent> TargetCursor;

	FTargetingEndedDelegate OnTargetingEnded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category= StatData)
	USSAICharacterStatData* AICharacterStatData;

	UPROPERTY()
	uint8 CurrentCombo;
};
