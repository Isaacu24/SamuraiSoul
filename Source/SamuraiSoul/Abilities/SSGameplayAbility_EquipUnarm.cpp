// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGameplayAbility_EquipUnarm.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/SSBehaviorInterface.h"
#include "SSGameplayTags.h"

USSGameplayAbility_EquipUnarm::USSGameplayAbility_EquipUnarm()
{
	AbilityID      = ESSAbilityID::EquipUnarm;
	AbilityInputID = ESSAbilityInputID::EquipUnarm;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_EquipUnarmTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_EquipUnarmTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_EquipUnarm::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_EquipUnarm::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_EquipUnarm::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const TWeakObjectPtr<AActor> Owner = GetActorInfo().AvatarActor;

	if (nullptr == Owner)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ISSBehaviorInterface* Character = Cast<ISSBehaviorInterface>(Owner);

	bool bIsEquip = false;

	if (nullptr != Character)
	{
		bIsEquip = Character->IsEquip();
		Character->SwitchIsEquip();
	}
	if (nullptr != EquipMontage
		&& nullptr != EquipRootMontage
		&& false == bIsEquip)
	{
		if (0.1f <= Owner->GetVelocity().Size())
		{
			//Not Root Anim Montage
			PlayMontage(EquipMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
		}

		else
		{
			//Root Anim Montage
			PlayMontage(EquipRootMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
		}
	}


	if (nullptr != UnarmMontage
		&& nullptr != UnarmRootMontage
		&& true == bIsEquip)
	{
		if (0.1f <= Owner->GetVelocity().Size())
		{
			//Not Root Anim Montage
			PlayMontage(UnarmMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
		}

		else
		{
			//Root Anim Montage
			PlayMontage(UnarmRootMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
		}
	}
}

void USSGameplayAbility_EquipUnarm::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_EquipUnarm::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_EquipUnarm::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
