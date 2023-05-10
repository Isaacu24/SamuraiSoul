// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SSGameplayAbility.h"
#include "SSGameplayAbility_Execution.generated.h"

class ASSCharacterBase;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSGameplayAbility_Execution : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGameplayAbility_Execution();

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual void AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;

	void Execution();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ExecutionMontage;

	FTimerHandle ExecutionTimerHandle;
	bool HasExecutionCommand;

	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;

	//UPROPERTY()
	//TObjectPtr<ASSCharacterBase> Enemy;

};
