// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyBossCombatComponent.h"
#include "Interface/SSCharacterAIInterface.h"

USSEnemyBossCombatComponent::USSEnemyBossCombatComponent()
{
}

void USSEnemyBossCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USSEnemyBossCombatComponent::Hit(EAttackType InType)
{
	Super::Hit(InType);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetHit(true);
	AIPawn->HidePerilousMark();
}
