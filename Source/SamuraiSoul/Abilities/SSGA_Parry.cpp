// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGA_Parry.h"
#include "SSGameplayTags.h"

USSGA_Parry::USSGA_Parry()
{
	AbilityID = ESSAbilityID::Parry;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_ParryTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_ParryTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
	ActivationBlockedTags.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_Parry::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(ParryMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGA_Parry::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                             const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGA_Parry::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_Parry::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
