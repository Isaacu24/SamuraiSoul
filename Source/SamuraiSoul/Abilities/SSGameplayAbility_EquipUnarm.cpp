// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGameplayAbility_EquipUnarm.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "../Character/SSSamuraiCharacter.h"

USSGameplayAbility_EquipUnarm::USSGameplayAbility_EquipUnarm()
{
	AbilityID = ESSAbilityID::EquipUnarm;
	AbilityInputID = ESSAbilityInputID::EquipUnarm;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.EquipUnarm")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.EquipUnarm")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_EquipUnarm::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputPressed: %s"), *GetName()));
}

void USSGameplayAbility_EquipUnarm::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputReleased: %s"), *GetName()));
}

void USSGameplayAbility_EquipUnarm::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(ActorInfo->OwnerActor);

	bool bIsEquip = false;

	if (nullptr != Character)
	{
		bIsEquip = Character->IsEquip();
		Character->SwitchIsEquip();
	}

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != EquipMontage
			&& nullptr != EquipRootMontage
			&& false == bIsEquip)
		{
			if (0.1f <= Character->GetVelocity().Size())
			{
				//Not Root Anim Montage
				USSAbilityTask_PlayMontageAndWait* Task
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, EquipMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

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
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, EquipRootMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

				Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
				Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
				Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
				Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
				Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

				Task->ReadyForActivation();
			}

		}


		if (nullptr != UnarmMontage
			&& nullptr != UnarmRootMontage
			&& true == bIsEquip)
		{
			if (0.1f <= Character->GetVelocity().Size())
			{
				//Not Root Anim Montage
				USSAbilityTask_PlayMontageAndWait* Task
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, UnarmMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

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
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, UnarmRootMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

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

void USSGameplayAbility_EquipUnarm::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_EquipUnarm::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}

void USSGameplayAbility_EquipUnarm::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{

}
