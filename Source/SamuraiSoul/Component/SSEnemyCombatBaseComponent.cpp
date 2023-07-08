// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatBaseComponent.h"
#include "SSEnemyCombatComponent.h"

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
