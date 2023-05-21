// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSBehaviorInterface.generated.h"

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

	virtual bool IsEquip() const = 0;

	virtual bool IsLockOn() const = 0;

	virtual void SwitchIsEquip() = 0;

	virtual bool IsDefense() const = 0;

	virtual void SwitchIsDefense() = 0;
};