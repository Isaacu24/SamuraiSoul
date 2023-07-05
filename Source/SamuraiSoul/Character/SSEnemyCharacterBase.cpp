// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacterBase.h"
#include <Components/CapsuleComponent.h>
#include "AI/SSEnemyAIController.h"
#include "DataAsset/SSAICharacterStatData.h"
#include "Component/SSEnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/SSWidgetComponent.h"
#include "AI/SSEnemyBaseAIController.h"

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

	PerilousMark = CreateDefaultSubobject<USSWidgetComponent>(TEXT("PerilousMark"));
	PerilousMark->SetupAttachment(GetMesh());
	PerilousMark->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget>
		PERILOUSMARK_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/WBP_Perilous.WBP_Perilous_C'"));

	if (true == PERILOUSMARK_WIDGET.Succeeded())
	{
		PerilousMark->SetWidgetClass(PERILOUSMARK_WIDGET.Class);
		PerilousMark->SetWidgetSpace(EWidgetSpace::Screen);
		PerilousMark->SetDrawSize(FVector2D(150.0f, 150.0f));
		PerilousMark->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	PerilousMark->SetHiddenInGame(true);
}

void ASSEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	ensure(AICharacterStatData);

	HideTargetUI();
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

float ASSEnemyCharacterBase::GetAIHearingRange()
{
	return AICharacterStatData->AIHearingRange;
}

float ASSEnemyCharacterBase::GetAIAttackRange()
{
	return AICharacterStatData->AIAttackRange;
}

void ASSEnemyCharacterBase::StopAI()
{
	ASSEnemyBaseAIController* AIController = Cast<ASSEnemyBaseAIController>(GetController());
	ensure(AIController);

	AIController->StopAI();
}

void ASSEnemyCharacterBase::RunAI()
{
	ASSEnemyBaseAIController* AIController = Cast<ASSEnemyBaseAIController>(GetController());
	ensure(AIController);

	AIController->RunAI();
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

void ASSEnemyCharacterBase::SetAIEquipUnarmDelegate(const FAICharacterAbilityFinished& InOnAttackFinished)
{
	OnEquipUnarmFinished = InOnAttackFinished;
}

void ASSEnemyCharacterBase::AttackByAI()
{
}


void ASSEnemyCharacterBase::AttackEnd()
{
	OnAttackFinished.ExecuteIfBound();
}

void ASSEnemyCharacterBase::EquipUnarm()
{
}

void ASSEnemyCharacterBase::EquipUnarmEnd()
{
	OnEquipUnarmFinished.ExecuteIfBound();
}

void ASSEnemyCharacterBase::ShowPerilousMark()
{
	PerilousMark->SetHiddenInGame(false);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [&]()
	{
		PerilousMark->SetHiddenInGame(true);
	}, 1.0f, false);
}

void ASSEnemyCharacterBase::HidePerilousMark()
{
	PerilousMark->SetHiddenInGame(true);
}

void ASSEnemyCharacterBase::SetParry(bool Value)
{
}

void ASSEnemyCharacterBase::SetHit(bool Value)
{
}

void ASSEnemyCharacterBase::SetDead(bool Value)
{
}

void ASSEnemyCharacterBase::SetRebound(bool Value)
{
}

void ASSEnemyCharacterBase::SetEquip(bool Value)
{
}

void ASSEnemyCharacterBase::SetBeExecuted(bool Value)
{
}

FTargetingEndedDelegate& ASSEnemyCharacterBase::GetTargetingEndedDelegate()
{
	return OnTargetingEnded;
}

void ASSEnemyCharacterBase::Die()
{
	Super::Die();
}

void ASSEnemyCharacterBase::VisibleTargetUI()
{
	ensure(TargetCursor);
	TargetCursor->SetHiddenInGame(false);
}

void ASSEnemyCharacterBase::HideTargetUI()
{
	ensure(TargetCursor);
	TargetCursor->SetHiddenInGame(true);
}

EAttackType ASSEnemyCharacterBase::GetWeaponAttakType() const
{
	return CombatComponent->GetWeapon()->GetAttackType();
}

void ASSEnemyCharacterBase::SetWeaponAttackType(EAttackType InType)
{
	CombatComponent->GetWeapon()->SetAttackType(InType);
}
