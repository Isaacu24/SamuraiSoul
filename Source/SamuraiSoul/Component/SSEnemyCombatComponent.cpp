// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Item/Weapon/SSWeapon.h"

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

void USSEnemyCombatComponent::Parry()
{
	Super::Parry();

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetParry(true);
}

void USSEnemyCombatComponent::Rebound()
{
	Super::Rebound();

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetRebound(true);
}

void USSEnemyCombatComponent::Hit()
{
	Super::Hit();

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetHit(true);
}
