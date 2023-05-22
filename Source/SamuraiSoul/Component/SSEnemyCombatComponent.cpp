// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Interface/SSCharacterAIInterface.h"

USSEnemyCombatComponent::USSEnemyCombatComponent()
{
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

void USSEnemyCombatComponent::Hit(const FHitResult& HitResult)
{
	Super::Hit(HitResult);

	ISSCharacterAIInterface* Character = Cast<ISSCharacterAIInterface>(GetOwner());

	if (nullptr != Character)
	{
		Character->StopBehaviorTree();
	}
}
