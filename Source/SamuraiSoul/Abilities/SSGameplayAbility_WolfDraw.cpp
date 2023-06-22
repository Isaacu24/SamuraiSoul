// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_WolfDraw.h"
#include "SSGameplayTags.h"
#include "GameFramework/Character.h"
#include "Interface/SSBehaviorInterface.h"

USSGameplayAbility_WolfDraw::USSGameplayAbility_WolfDraw()
{
	AbilityID = ESSAbilityID::WolfDraw;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_WolfDrawTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_WolfDrawTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_WolfDraw::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
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

	PlayMontage(Montage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_WolfDraw::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
