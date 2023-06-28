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
			TryActivateAbility(SlashTag);
			break;
		case EWeaponType::Bow:
			// Active Ability
			break;
		default:
			break;
	}
}

void USSEnemyCombatComponent::SpecialAttackByAI(const FGameplayTag& Tag) const
{
	TryActivateAbility(Tag);
}

void USSEnemyCombatComponent::Equip()
{
	TryActivateAbility(EquipTag);
}

void USSEnemyCombatComponent::Parry(AActor* InActor)
{
	Super::Parry(InActor);

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
	AIPawn->HidePerilousMark();
}

void USSEnemyCombatComponent::BeExecuted(int8 RandomNumber)
{
	Super::BeExecuted(RandomNumber);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetBeExecuted(true);
}
