// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacterBase.h"
#include <Components/CapsuleComponent.h>
#include "DataAsset/SSAICharacterStatData.h"
#include "Component/SSEnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/SSWidgetComponent.h"
#include "AI/SSEnemyAIController.h"

ASSEnemyCharacterBase::ASSEnemyCharacterBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	CombatComponent                      = CreateDefaultSubobject<USSEnemyCombatComponent>(TEXT("Combat Component"));
	GetCharacterMovement()->MaxWalkSpeed = 100.f;

	TargetCursor = CreateDefaultSubobject<USSWidgetComponent>(TEXT("Cursor"));
	TargetCursor->SetupAttachment(GetMesh());
	TargetCursor->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget>
		CURSOR_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/WBP_TargetCursor.WBP_TargetCursor_C'"));

	if (true == CURSOR_WIDGET.Succeeded())
	{
		TargetCursor->SetWidgetClass(CURSOR_WIDGET.Class);
		TargetCursor->SetWidgetSpace(EWidgetSpace::Screen);
		TargetCursor->SetDrawSize(FVector2D(10.0f, 10.0f));
		TargetCursor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASSEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	ensure(AICharacterStatData);

	SetHiddenTargetCursor(true);
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

void ASSEnemyCharacterBase::SetParry(bool Value)
{
	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());
	ensure(AIController);

	AIController->SetParry(Value);
}

void ASSEnemyCharacterBase::SetHit(bool Value)
{
	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());
	ensure(AIController);

	AIController->SetHit(Value);
}

void ASSEnemyCharacterBase::SetDead(bool Value)
{
	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());
	ensure(AIController);

	AIController->SetDead(Value);
}

void ASSEnemyCharacterBase::SetRebound(bool Value)
{
	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());
	ensure(AIController);

	AIController->SetRebound(Value);
}

void ASSEnemyCharacterBase::SetHiddenHPBar(bool Value) const
{
}

void ASSEnemyCharacterBase::SetHiddenTargetCursor(bool Value) const
{
	if (nullptr != TargetCursor)
	{
		TargetCursor->SetHiddenInGame(Value);
	}
}
