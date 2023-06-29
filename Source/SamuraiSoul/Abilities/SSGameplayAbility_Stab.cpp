// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_Stab.h"
#include "SSGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Interface/SSBehaviorInterface.h"
#include "Interface/SSCharacterAIInterface.h"

USSGameplayAbility_Stab::USSGameplayAbility_Stab()
{
	AbilityID = ESSAbilityID::Stab;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_StabTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_StabTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_Stab::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MyCharacter = Cast<ACharacter>(ActorInfo->OwnerActor);
	check(MyCharacter);

	MyCollisionProfileName = MyCharacter->GetCapsuleComponent()->GetCollisionProfileName();
	MyCharacter->GetCapsuleComponent()->SetCollisionProfileName(FName("InvincibleCharacter"));

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(MyCharacter);

	if (nullptr != BehaviorPawn)
	{
		if (false == BehaviorPawn->IsEquip())
		{
			Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
	}

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(MyCharacter);

	if (nullptr != AI)
	{
		AI->ShowPerilousMark();
	}

	PlayMontage(StabMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Stab::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (nullptr == MyCharacter)
	{
		return;
	}

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(MyCharacter);

	if (nullptr != AI)
	{
		AI->AttackEnd();
	}

	MyCharacter->GetCapsuleComponent()->SetCollisionProfileName(MyCollisionProfileName);
}
