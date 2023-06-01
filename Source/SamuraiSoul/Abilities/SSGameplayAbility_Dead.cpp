// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/SSGameplayAbility_Dead.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Dead::USSGameplayAbility_Dead()
{
	AbilityID      = ESSAbilityID::Dead;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FSSGameplayTags::Get().DeadTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().DeadTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().DeadTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_Dead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Dead::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Dead::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}
