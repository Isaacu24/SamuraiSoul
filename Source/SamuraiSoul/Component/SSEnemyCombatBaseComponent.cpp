// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatBaseComponent.h"
#include "SSEnemyCombatComponent.h"
#include "Interface/SSCharacterAIInterface.h"

USSEnemyCombatBaseComponent::USSEnemyCombatBaseComponent()
{
}

void USSEnemyCombatBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USSEnemyCombatBaseComponent::SetEnemyWeapon() const
{
	Weapon->SetEnemyWeapon();
}

void USSEnemyCombatBaseComponent::AttackByAI() const
{
}

void USSEnemyCombatBaseComponent::SpecialAttackByAI(const FGameplayTag& AbilityTag) const
{
	TryActivateAbility(AbilityTag);
}

void USSEnemyCombatBaseComponent::Rebound()
{
	Super::Rebound();

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetRebound(true);
}
