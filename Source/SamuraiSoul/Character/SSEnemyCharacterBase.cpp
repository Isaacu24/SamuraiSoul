// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacterBase.h"
#include <Components/CapsuleComponent.h>
#include "Component/SSWidgetComponent.h"
#include "Component/SSEnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASSEnemyCharacterBase::ASSEnemyCharacterBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	HPBar = CreateDefaultSubobject<USSWidgetComponent>(TEXT("Widget"));
	HPBar->SetupAttachment(GetMesh());
	HPBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HPBAR_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/WBP_HPBar.WBP_HPBar_C'"));

	if (true == HPBAR_WIDGET.Succeeded())
	{
		HPBar->SetWidgetClass(HPBAR_WIDGET.Class);
		HPBar->SetWidgetSpace(EWidgetSpace::Screen);
		HPBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HPBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	GetCharacterMovement()->MaxWalkSpeed = 100.f;

	CombatComponent = CreateDefaultSubobject<USSEnemyCombatComponent>(TEXT("Combat Component"));
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
