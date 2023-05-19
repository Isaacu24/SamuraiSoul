// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>
#include "SSGameplayAbility.h"
#include "SSGameplayAbility_Slash.generated.h"

class USSComboActionData;
class UAnimInstance;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSGameplayAbility_Slash : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGameplayAbility_Slash();

	virtual void InputPressed(const FGameplayAbilitySpecHandle     Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                          const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle     Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                           const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle     Handle, const FGameplayAbilityActorInfo*  ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle     Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool                     bReplicateEndAbility, bool bWasCancelled) override;

	/* CommitCost()는 어빌리티가 활성되기 전에 비용 지불이 가능한지 확인하고 지불함. 반면에 ApplyCost()는 어빌리티가 활성된 후 지불이 가능한지 확인하고 지불함. */
	virtual void ApplyCost(const FGameplayAbilitySpecHandle     Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                       const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual void AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> SlashMontage;

	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboData, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSComboActionData> SlashComboData;

	int32        CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool         HasNextComboCommand = false;

	void SetComboCheckTimer();
	void ComboCheck();
};
