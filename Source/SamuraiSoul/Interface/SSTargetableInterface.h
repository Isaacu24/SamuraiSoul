// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSTargetableInterface.generated.h"

DECLARE_DELEGATE(FTargetingEndedDelegate);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMURAISOUL_API ISSTargetableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual FTargetingEndedDelegate& GetTargetingEndedDelegate() = 0;

	virtual void VisibleTargetUI() = 0;
	virtual void HideTargetUI() = 0;
};
