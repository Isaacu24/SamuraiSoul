// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/SSGA_SpinSlash.h"
#include "SSGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Interface/SSBehaviorInterface.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Interface/SSCombatableInterface.h"

USSGA_SpinSlash::USSGA_SpinSlash()
{
	AbilityID = ESSAbilityID::SpinSlash;

	//AbilityTags.AddTag(FSSGameplayTags::Get().Ability_SpinSlashTag);
	//ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_SpinSlashTag);
	//BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_SpinSlash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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

	ISSCombatableInterface* CombatPawn = Cast<ISSCombatableInterface>(MyCharacter);

	if (nullptr != CombatPawn)
	{
		CombatPawn->SetWeaponAttackType(EAttackType::SpecialAttack);
	}

	PlayMontage(SpinSlashMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGA_SpinSlash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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

	ISSCombatableInterface* CombatPawn = Cast<ISSCombatableInterface>(MyCharacter);

	if (nullptr != CombatPawn)
	{
		CombatPawn->SetWeaponAttackType(EAttackType::Normal);
	}

	MyCharacter->GetCapsuleComponent()->SetCollisionProfileName(MyCollisionProfileName);
}
