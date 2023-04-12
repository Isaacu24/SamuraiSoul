// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSGameplayAbility.h"
#include "SSGameplayAbility_Dodege.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSGameplayAbility_Dodege : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	USSGameplayAbility_Dodege();

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/* CommitCost()�� �����Ƽ�� Ȱ���Ǳ� ���� ��� ������ �������� Ȯ���ϰ� ������. �ݸ鿡 ApplyCost()�� �����Ƽ�� Ȱ���� �� ������ �������� Ȯ���ϰ� ������. */
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	UFUNCTION()
		void AbilityCompleted(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
		void AbilityBlendOut(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
		void AbilityInterrupted(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
		void AbilityCancelled(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
		void AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DodgeMontage;
};
