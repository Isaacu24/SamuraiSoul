// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGameplayAbility_BeExecuted.h"
#include <GameFramework/Character.h>
#include <Components/CapsuleComponent.h>
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/SSTargetableInterface.h"
#include "SSGameplayTags.h"

USSGameplayAbility_BeExecuted::USSGameplayAbility_BeExecuted()
{
	AbilityID      = ESSAbilityID::BeExecuted;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FSSGameplayTags::Get().BeExecutedTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().BeExecutedTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().ReactionTag);
	ActivationRequiredTags.AddTag(FSSGameplayTags::Get().ReboundTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().BeExecutedTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_BeExecuted::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->OwnerActor);
	check(Character);
	ISSTargetableInterface* TargetPawn = Cast<ISSTargetableInterface>(Character);

	if (nullptr != TargetPawn)
	{
		TargetPawn->GetTargetingEndedDelegate().ExecuteIfBound();
	}

	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("BeExecuted"));

	PlayMontage(ExecutedMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_BeExecuted::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_BeExecuted::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_BeExecuted::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
