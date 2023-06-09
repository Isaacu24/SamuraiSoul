// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SSGameplayAbility.h"
#include "SSGA_SpinSlash.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSGA_SpinSlash : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGA_SpinSlash();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> SpinSlashMontage;

	UPROPERTY()
	ACharacter* MyCharacter;

	UPROPERTY()
	FName MyCollisionProfileName;
};
