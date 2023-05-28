// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
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
	Super::Hit(InActor);

	ISSCharacterAIInterface* Character = Cast<ISSCharacterAIInterface>(GetOwner());

	if (nullptr != Character)
	{
		Character->StopBehaviorTree();
	}
}

void USSEnemyCombatComponent::Parry(AActor* Opponent)
{
	Super::Parry(Opponent);

	ISSCharacterAIInterface* Character = Cast<ISSCharacterAIInterface>(GetOwner());

	if (nullptr != Character)
	{
		Character->StopBehaviorTree();
	}
}

void USSEnemyCombatComponent::Rebound(AActor* Opponent)
{
	Super::Rebound(Opponent);

	ISSCharacterAIInterface* Character = Cast<ISSCharacterAIInterface>(GetOwner());

	if (nullptr != Character)
	{
		Character->StopBehaviorTree();
	}
}
