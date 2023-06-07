// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
};
