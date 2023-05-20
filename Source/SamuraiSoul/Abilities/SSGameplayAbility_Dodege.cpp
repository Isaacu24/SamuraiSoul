// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Dodege.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/SSSamuraiCharacter.h"

USSGameplayAbility_Dodege::USSGameplayAbility_Dodege()
{
	AbilityID      = ESSAbilityID::Dodge;
	AbilityInputID = ESSAbilityInputID::Dodge;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Dodge")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Dodge")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
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

	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(ActorInfo->OwnerActor);

	if (nullptr == Character
		|| false == Character->IsEquip())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != DodgeMontage)
		{
			USSAbilityTask_PlayMontageAndWait* Task
				= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, DodgeMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

			Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
			Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
			Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
			Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
			Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

			Task->ReadyForActivation();
		}
	}
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
