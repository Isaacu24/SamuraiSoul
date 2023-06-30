// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SamuraiSoul.h"
#include "UObject/Interface.h"
#include "SSCombatableInterface.generated.h"

class USSCombatComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSCombatableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMURAISOUL_API ISSCombatableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual USSCombatComponent* GetCombatComponent() const = 0;

	//for Attack Animation Cancel.
	virtual const bool GetHasNextComboCommand() const = 0;
	virtual const void SetHasNextComboCommand(const bool Value) = 0;

	virtual EAttackType GetWeaponAttakType() const = 0;
	virtual void SetWeaponAttackType(EAttackType InType) = 0;

	virtual bool GetCanEnemyExecution() const = 0;
	virtual void SetCanEnemyExecution(bool Value) = 0;
};
