// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Dodege.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/SSBehaviorInterface.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Dodege::USSGameplayAbility_Dodege()
{
	AbilityID      = ESSAbilityID::Dodge;
	AbilityInputID = ESSAbilityInputID::Dodge;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_DodgeTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_DodgeTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_Dodege::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Dodege::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Dodege::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(ActorInfo->OwnerActor);

	if (nullptr == BehaviorPawn
		|| false == BehaviorPawn->IsEquip())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	PlayMontage(DodgeMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Dodege::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Dodege::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Dodege::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
