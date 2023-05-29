// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacterBase.h"
#include <Components/CapsuleComponent.h>
#include "Component/SSEnemyCombatComponent.h"
#include "DataAsset/SSAICharacterStatData.h"
#include "GameFramework/CharacterMovementComponent.h"

ASSEnemyCharacterBase::ASSEnemyCharacterBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	CombatComponent                      = CreateDefaultSubobject<USSEnemyCombatComponent>(TEXT("Combat Component"));
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

void ASSEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	ensure(AICharacterStatData);
}

float ASSEnemyCharacterBase::GetAIPatrolRadius()
{
	return AICharacterStatData->AIPatrolRadius;
}

float ASSEnemyCharacterBase::GetAIDetectRadius()
{
	return AICharacterStatData->AIDetectRadius;
}

float ASSEnemyCharacterBase::GetAILoseDetectRadius()
{
	return AICharacterStatData->AILoseDetectRadius;
}

float ASSEnemyCharacterBase::GetAISight()
{
	return AICharacterStatData->AISight;
}

float ASSEnemyCharacterBase::GetAIAttackRange()
{
	return AICharacterStatData->AIAttackRange;
}

float ASSEnemyCharacterBase::GetAITurnSpeed()
{
	return AICharacterStatData->AITurnSpeed;
}

void ASSEnemyCharacterBase::Run()
{
}

void ASSEnemyCharacterBase::Walk()
{
}

void ASSEnemyCharacterBase::SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ASSEnemyCharacterBase::AttackByAI()
{
}

void ASSEnemyCharacterBase::AttackEnd()
{
	OnAttackFinished.ExecuteIfBound();
}

void ASSEnemyCharacterBase::RunBehaviorTree() const
{
}

void ASSEnemyCharacterBase::StopBehaviorTree() const
{
}

void ASSEnemyCharacterBase::SetAICharacterStatData(USSAICharacterStatData* AICharacterData)
{
}
