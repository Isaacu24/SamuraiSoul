// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/SSGameplayAbility_SpinSlash.h"
#include "SSGameplayTags.h"
#include "GameFramework/Character.h"
#include "Interface/SSBehaviorInterface.h"
#include "Interface/SSCharacterAIInterface.h"

USSGameplayAbility_SpinSlash::USSGameplayAbility_SpinSlash()
{
	AbilityID = ESSAbilityID::SpinSlash;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_SpinSlashTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_SpinSlashTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_SpinSlash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->OwnerActor);
	check(Character);

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(Character);

	if (nullptr != BehaviorPawn)
	{
		if (false == BehaviorPawn->IsEquip())
		{
			Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
	}

	PlayMontage(SpinSlashMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_SpinSlash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(ActorInfo->OwnerActor);

	if (nullptr != AI)
	{
		AI->AttackEnd();
	}
}