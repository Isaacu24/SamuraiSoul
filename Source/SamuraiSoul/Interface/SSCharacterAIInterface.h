// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "SSCharacterAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSCharacterAIInterface : public UInterface
{
	GENERATED_BODY()
};


DECLARE_DELEGATE(FAICharacterAbilityFinished);

/**
 * 
 */
class SAMURAISOUL_API ISSCharacterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() = 0;
	virtual float GetAIDetectRadius() = 0;
	virtual float GetAILoseDetectRadius() = 0;
	virtual float GetAISight() = 0;
	virtual float GetAIHearingRange() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual bool GetAIIsStartPatrol() = 0;

	virtual uint8 GetCurrentCombo() = 0;

	virtual void StopAI() = 0;
	virtual void RunAI() = 0;

	virtual void Run() = 0;
	virtual void Walk() = 0;

	virtual void SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished) = 0;
	virtual void SetAIEquipUnarmDelegate(const FAICharacterAbilityFinished& InOnEquipUnarmFinished) = 0;
	virtual void SetAIDefenseDelegate(const FAICharacterAbilityFinished& InOnDefenseeFinished) = 0;

	virtual void AttackByAI() = 0;
	virtual void AttackEnd() = 0;

	virtual void EquipUnarmByAI() = 0;
	virtual void EquipUnarmEnd() = 0;

	virtual void DefenseByAI() = 0;
	virtual void DefenseEnd() = 0;

	virtual void SetAssassinationCollision(bool Value)
	{
	};

	virtual void ShowPerilousMark() = 0;
	virtual void HidePerilousMark() = 0;

	virtual void SetParry(bool Value) = 0;

	virtual void SetHit(bool Value) = 0;
	virtual void SetDead(bool Value) = 0;
	virtual void SetRebound(bool Value) = 0;
	virtual void SetEquip(bool Value) = 0;
	virtual void SetBeExecuted(bool Value) = 0;
};
