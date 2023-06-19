// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Hit.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Hit::USSGameplayAbility_Hit()
{
	AbilityID = ESSAbilityID::Hit;

	AbilityTags.AddTag(FSSGameplayTags::Get().HitTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().HitTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().HitTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_Hit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(ForwardHitMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Hit::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ActorInfo->OwnerActor);

	if (nullptr != AIPawn)
	{
		AIPawn->SetHit(false);
	}
}

void USSGameplayAbility_Hit::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}
