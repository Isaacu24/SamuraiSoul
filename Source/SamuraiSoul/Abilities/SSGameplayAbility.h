// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../Game/SamuraiSoul.h"
#include "SSGameplayAbility.generated.h"

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

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Ability")
	ESSAbilityInputID AbilityInputID = ESSAbilityInputID::None;
	
	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Ability")
	ESSAbilityID AbilityID = ESSAbilityID::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Handles)
	mutable FActiveGameplayEffectHandle EffectHandle;

};
