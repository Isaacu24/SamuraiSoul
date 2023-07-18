// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGA_Defense.h"
#include <GameFramework/Character.h>
#include "SSAbilityTask.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatableInterface.h"
#include "SSGameplayTags.h"
#include "Interface/SSCharacterAIInterface.h"

USSGA_Defense::USSGA_Defense()
{
	AbilityID = ESSAbilityID::Defense;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_DefenseTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_DefenseTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_Defense::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGA_Defense::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}

void USSGA_Defense::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	OwnerCharacter                                    = Cast<ACharacter>(ActorInfo->OwnerActor);
	const ISSCombatableInterface* CombatableCharacter = Cast<ISSCombatableInterface>(OwnerCharacter);

	CombatableCharacter->GetCombatComponent()->OnDefense();
	CombatableCharacter->GetCombatComponent()->BindDefenseHit()->OnHitEvent.BindUObject(this, &USSGA_Defense::DefenseHit);

	PlayMontage(DefenseMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//if (0.1f <= ActorInfo->OwnerActor->GetVelocity().Size())
	//{
	//	//Not Root Anim Montage
	//	PlayMontage(DefenseMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//}

	//else
	//{
	//	//Root Anim Montage
	//	PlayMontage(DefenseRootMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//}
}

void USSGA_Defense::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	HitStack = 0;

	ISSCombatableInterface* Combatable = Cast<ISSCombatableInterface>(OwnerCharacter);

	if (nullptr != OwnerCharacter
		&& nullptr != Combatable)
	{
		Combatable->GetCombatComponent()->OffDefense();

		if (nullptr != OwnerCharacter->GetMesh()->GetAnimInstance())
		{
			OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseLEnd"), DefenseMontage);
			//OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseLEnd"), DefenseRootMontage);
		}
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ActorInfo->OwnerActor);

	if (nullptr != AIPawn)
	{
		AIPawn->DefenseEnd();
	}
}

void USSGA_Defense::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_Defense::DefenseHit()
{
	switch (HitStack)
	{
		case 0:
			OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseHit"), DefenseMontage);
		//OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseHit"), DefenseRootMontage);
			break;
		case 1:
			OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseHit1"), DefenseMontage);
		//OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseHit1"), DefenseRootMontage);
			break;

		case 2:
			OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseHit2"), DefenseMontage);
		//OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseHit2"), DefenseRootMontage);
			break;
	}

	++HitStack;
}
