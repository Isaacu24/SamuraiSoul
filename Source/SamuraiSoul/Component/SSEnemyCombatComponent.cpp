// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "SSGameplayTags.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Interface/SSCharacterAIInterface.h"

USSEnemyCombatComponent::USSEnemyCombatComponent()
{
}

void USSEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USSEnemyCombatComponent::SetEnemyWeapon() const
{
	Weapon->SetEnemyWeapon();
}

// AI 
void USSEnemyCombatComponent::AttackByAI() const
{
	switch (Weapon->GetWeaponType())
	{
		case EWeaponType::Katana:
			ActivateAbility(SlashAbility);
			break;
		case EWeaponType::Bow:
			// Active Ability
			break;
		default:
			break;
	}
}

void USSEnemyCombatComponent::Hit(AActor* InActor)
{
	//Super::Hit(InActor);

	//IAbilitySystemInterface* Ability = Cast<IAbilitySystemInterface>(GetOwner());
	//ISSCharacterAIInterface* AIPawn  = Cast<ISSCharacterAIInterface>(GetOwner());

	//if (nullptr != Ability
	//	&& nullptr != AIPawn)
	//{
	//	AIPawn->SetHit(true);
	//	Ability->GetAbilitySystemComponent()->AddLooseGameplayTag(FSSGameplayTags::Get().HitTag);
	//}
}

void USSEnemyCombatComponent::Parry(AActor* Opponent)
{
	Super::Parry(Opponent);
}

void USSEnemyCombatComponent::Rebound(AActor* Opponent)
{
	Super::Rebound(Opponent);
}
