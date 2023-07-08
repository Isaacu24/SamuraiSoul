// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSGameplayAbility.h"
#include "SSGA_Dodge.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSGA_Dodge : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGA_Dodge();

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                          const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                           const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/* CommitCost()�� �����Ƽ�� Ȱ���Ǳ� ���� ��� ������ �������� Ȯ���ϰ� ������. �ݸ鿡 ApplyCost()�� �����Ƽ�� Ȱ���� �� ������ �������� Ȯ���ϰ� ������. */
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                       const FGameplayAbilityActivationInfo ActivationInfo) const override;

	void AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UAnimMontage>> DodgeMontages;

	UPROPERTY()
	ACharacter* MyCharacter;

	UPROPERTY()
	FName MyCollisionProfileName;
};
