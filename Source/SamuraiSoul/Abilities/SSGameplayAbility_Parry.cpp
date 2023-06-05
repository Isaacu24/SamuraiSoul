// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_Parry.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Parry::USSGameplayAbility_Parry()
{
	AbilityID = ESSAbilityID::Parry;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FSSGameplayTags::Get().BeExecutedTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().BeExecutedTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FSSGameplayTags::Get().BeExecutedTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_Parry::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(ParryMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Parry::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Parry::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Parry::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
