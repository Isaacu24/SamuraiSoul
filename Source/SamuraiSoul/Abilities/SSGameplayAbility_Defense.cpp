// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Defense.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Component/SSCombatComponent.h"
#include "Character/SSSamuraiCharacter.h"

USSGameplayAbility_Defense::USSGameplayAbility_Defense()
{
	AbilityID = ESSAbilityID::Defense;
	AbilityInputID = ESSAbilityInputID::Defense;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Defense")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Defense")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_Defense::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputPressed: %s"), *GetName()));
}

void USSGameplayAbility_Defense::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputReleased: %s"), *GetName()));
}

void USSGameplayAbility_Defense::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(ActorInfo->OwnerActor);

	bool bIsEquip = false;

	if (nullptr == Character)
	{
		return;
	}

	Character->GetCombatComponent()->OnDefense();

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != DefenseMontage
			&& nullptr != DefenseRootMontage)
		{
			if (0.1f <= Character->GetVelocity().Size())
			{
				//Not Root Anim Montage
				USSAbilityTask_PlayMontageAndWait* Task
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, DefenseMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

				Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
				Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
				Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
				Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
				Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

				Task->ReadyForActivation();
			}

			else
			{
				//Root Anim Montage
				USSAbilityTask_PlayMontageAndWait* Task
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, DefenseRootMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

				Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
				Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
				Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
				Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
				Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

				Task->ReadyForActivation();
			}

		}
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ActivateAbility: %s"), *GetName()));
}

void USSGameplayAbility_Defense::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(ActorInfo->OwnerActor);

	if (nullptr != Character)
	{
		Character->GetCombatComponent()->OffDefense();
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_Defense::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}

void USSGameplayAbility_Defense::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
