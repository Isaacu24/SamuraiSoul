// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/SSGA_Dead.h"
#include "Interface/SSTargetableInterface.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSGameplayTags.h"

USSGA_Dead::USSGA_Dead()
{
	AbilityID = ESSAbilityID::Dead;

	AbilityTags.AddTag(FSSGameplayTags::Get().DeadTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().DeadTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().ReactionTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().DeadTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGA_Dead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ActorInfo->OwnerActor);

	if (nullptr != AIPawn)
	{
		AIPawn->SetDead(true);
	}

	ISSTargetableInterface* TargetPawn = Cast<ISSTargetableInterface>(ActorInfo->OwnerActor);

	if (nullptr != TargetPawn)
	{
		TargetPawn->GetTargetingEndedDelegate().ExecuteIfBound();
	}

	PlayMontage(DeadMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGA_Dead::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGA_Dead::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                           const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}
