// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGameplayAbility_BeExecuted.h"
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Character.h>
#include <Components/CapsuleComponent.h>
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"

USSGameplayAbility_BeExecuted::USSGameplayAbility_BeExecuted()
{
	AbilityID      = ESSAbilityID::BeExecuted;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.BeExecuted")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.BeExecuted")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_BeExecuted::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->OwnerActor);

	if (nullptr == Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("BeExecuted"));

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != ExecutedMontage)
		{
			USSAbilityTask_PlayMontageAndWait* Task
				= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, ExecutedMontage, FGameplayTagContainer(), 1.f, NAME_None,
				                                                                false);

			Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
			Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
			Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
			Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
			Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

			Task->ReadyForActivation();
		}
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ActivateAbility: %s"), *GetName()));
}

void USSGameplayAbility_BeExecuted::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_BeExecuted::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}

void USSGameplayAbility_BeExecuted::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
