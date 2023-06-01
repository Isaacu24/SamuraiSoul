// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Hit.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Component/SSCombatComponent.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Hit::USSGameplayAbility_Hit()
{
	AbilityID      = ESSAbilityID::Hit;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FSSGameplayTags::Get().HitTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().HitTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().HitTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_Hit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != FrontHitMontage)
		{
			USSAbilityTask_PlayMontageAndWait* Task
				= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, FrontHitMontage, FGameplayTagContainer(), 1.f, NAME_None,
				                                                                false);

			Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
			Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
			Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
			Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
			Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

			Task->ReadyForActivation();
		}
	}
}

void USSGameplayAbility_Hit::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Hit::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}
