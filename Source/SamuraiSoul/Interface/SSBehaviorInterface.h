// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSBehaviorInterface.generated.h"

DECLARE_MULTICAST_DELEGATE(FCharacterLandedDelegate);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSBehaviorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMURAISOUL_API ISSBehaviorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsCrouch() const = 0;
	virtual bool IsHit() const = 0;

	virtual bool IsLockOn() const = 0;

	virtual bool IsEquip() const = 0;
	virtual void SwitchIsEquip() = 0;

	virtual bool IsDefense() const = 0;
	virtual void SwitchIsDefense() = 0;

	virtual bool IsDown() const = 0;
	virtual void SetIsDown(bool Value) = 0;

	virtual const FVector2D& GetMovementVector() const = 0;
	virtual const bool GetAxisInput() const = 0;

	virtual FCharacterLandedDelegate& GetCharacterLandedEvnet() = 0;

	virtual bool IsDie() const = 0;
};
