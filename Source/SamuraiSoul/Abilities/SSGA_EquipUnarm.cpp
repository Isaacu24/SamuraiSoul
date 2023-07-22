// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGA_EquipUnarm.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/SSBehaviorInterface.h"
#include "SSGameplayTags.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Character/SSCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

USSGA_EquipUnarm::USSGA_EquipUnarm()
{
	AbilityID = ESSAbilityID::EquipUnarm;

	//AbilityTags.AddTag(FSSGameplayTags::Get().Ability_EquipUnarmTag);
	//ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_EquipUnarmTag);
	//BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_EquipUnarm::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGA_EquipUnarm::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGA_EquipUnarm::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const TWeakObjectPtr<AActor> Owner = GetActorInfo().AvatarActor;

	if (nullptr == Owner)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(Owner);

	bIsEquip = false;

	if (nullptr != BehaviorPawn)
	{
		bIsEquip = BehaviorPawn->IsEquip();
		BehaviorPawn->SwitchIsEquip();
	}

	if (nullptr != EquipMontage
		&& nullptr != EquipRootMontage
		&& false == bIsEquip)
	{
		if (0.1f <= Owner->GetVelocity().Size())
		{
			//Not Root Anim Montage
			PlayMontage(EquipMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
			UE_LOG(LogTemp, Error, TEXT("EquipMontage"));
		}

		else
		{
			//Root Anim Montage
			PlayMontage(EquipRootMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
			UE_LOG(LogTemp, Error, TEXT("EquipMontage"));
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

void USSGA_EquipUnarm::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ActorInfo->OwnerActor);

	if (nullptr != AIPawn)
	{
		if (false == bIsEquip)
		{
			AIPawn->SetEquip(true);
		}

		AIPawn->EquipUnarmEnd();
	}
}

void USSGA_EquipUnarm::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_EquipUnarm::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
