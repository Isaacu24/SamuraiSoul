// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_BeAssassinated.h"
#include "SSGameplayTags.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Interface/SSCombatableInterface.h"
#include "Interface/SSTargetableInterface.h"

USSGameplayAbility_BeAssassinated::USSGameplayAbility_BeAssassinated()
{
	AbilityID = ESSAbilityID::BeAssassinated;

	AbilityTags.AddTag(FSSGameplayTags::Get().BeAssassinatedTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().BeAssassinatedTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().ReactionTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().BeAssassinatedTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_BeAssassinated::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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

	ISSCombatableInterface* CombatablePawn = Cast<ISSCombatableInterface>(ActorInfo->OwnerActor);
	int8 Number                            = CombatablePawn->GetCombatComponent()->GetAssassinationNumber();

	PlayMontage(AssassinatedMontages[Number], Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_BeAssassinated::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_BeAssassinated::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_BeAssassinated::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
