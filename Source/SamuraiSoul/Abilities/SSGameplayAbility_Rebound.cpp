// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_Rebound.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Rebound::USSGameplayAbility_Rebound()
{
	AbilityID = ESSAbilityID::Rebound;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FSSGameplayTags::Get().ReboundTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().ReboundTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FSSGameplayTags::Get().ReboundTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_Rebound::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(ReboundMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Rebound::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Rebound::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}
