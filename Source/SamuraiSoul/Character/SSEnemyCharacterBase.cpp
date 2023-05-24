// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacterBase.h"
#include <Components/CapsuleComponent.h>

ASSEnemyCharacterBase::ASSEnemyCharacterBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
}

float ASSEnemyCharacterBase::GetAIPatrolRadius()
{
	return 800.0f;
}

float ASSEnemyCharacterBase::GetAIDetectRange()
{
	return 800.0f;
}

float ASSEnemyCharacterBase::GetAISight()
{
	return 60.0f;
}

float ASSEnemyCharacterBase::GetAIAttackRange()
{
	return 250.0f;
}

float ASSEnemyCharacterBase::GetAITurnSpeed()
{
	return 0.0f;
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
