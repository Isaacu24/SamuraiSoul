// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../SamuraiSoul.h"
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

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Ability")
	ESSAbilityInputID AbilityInputID = ESSAbilityInputID::None;
	
	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Ability")
	ESSAbilityID AbilityID = ESSAbilityID::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Handles)
	mutable FActiveGameplayEffectHandle EffectHandle;

};
