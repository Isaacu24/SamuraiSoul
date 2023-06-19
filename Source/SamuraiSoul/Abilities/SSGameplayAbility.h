// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../Game/SamuraiSoul.h"
#include "SSGameplayAbility.generated.h"

/**
 *	Defines how an ability is meant to activate.
 */
UENUM(BlueprintType)
enum class ESSAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};


/**
 *	Defines how an ability activates in relation to other abilities.
 */
UENUM(BlueprintType)
enum class ESSAbilityActivationGroup : uint8
{
	// Ability runs independently of all other abilities.
	Independent,

	// Ability is canceled and replaced by other exclusive abilities.
	Exclusive_Replaceable,

	// Ability blocks all other exclusive abilities from activating.
	Exclusive_Blocking,

	MAX UMETA(Hidden)
};

/** Failure reason that can be used to play an animation montage when a failure occurs */
USTRUCT(BlueprintType)
struct FSSAbilityMontageFailureMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	// All the reasons why this ability has failed
	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer FailureTags;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimMontage> FailureMontage = nullptr;
};


/**
 *
 */
UCLASS()
class SAMURAISOUL_API USSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USSGameplayAbility();

	UFUNCTION()
	virtual void AbilityCompleted(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void AbilityBlendOut(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void AbilityInterrupted(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void AbilityCancelled(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload);

	ESSAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

public:
	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Ability")
	ESSAbilityID AbilityID = ESSAbilityID::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Handles)
	mutable FActiveGameplayEffectHandle EffectHandle;

protected:
	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	ESSAbilityActivationPolicy ActivationPolicy;

protected:
	void CancelAllAbility();

	void PlayMontage(UAnimMontage* Montage, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
};
