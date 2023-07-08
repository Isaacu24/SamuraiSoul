// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SSGameplayAbility.h"
#include "SSGA_Execution.generated.h"

class ASSCharacterBase;

DECLARE_DELEGATE(FExecutionDelegate);

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSGA_Execution : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGA_Execution();

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                          const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                           const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                       const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual void AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<TObjectPtr<UAnimMontage>> ExecutionMontages;
};
