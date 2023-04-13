// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Dodege.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "../SSSamuraiCharacter.h"

USSGameplayAbility_Dodege::USSGameplayAbility_Dodege()
{
	AbilityID = ESSAbilityID::Dodge;
	AbilityInputID = ESSAbilityInputID::Dodge;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Dodge")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Dodge")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_Dodege::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	// Multyplay Debuging
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputPressed: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputReleased: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

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

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ActivateAbility: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
