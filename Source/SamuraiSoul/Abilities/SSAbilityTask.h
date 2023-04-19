// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SSAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSSPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	USSAbilityTask(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;
};
