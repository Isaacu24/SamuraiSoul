// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSEnemyBossCharacter.h"
#include "AI/SSEnemyBossAIController.h"
#include "Component/SSEnemyCombatComponent.h"
#include "Animation/SSEnemyBossAnimInstance.h"

ASSEnemyBossCharacter::ASSEnemyBossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/BossyEnemy/SkeletalMesh/SK_Mannequin_UE4_WithWeapon.SK_Mannequin_UE4_WithWeapon'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		ANIM_ENEMY(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyBossCharacter.AB_SSEnemyBossCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_ENEMY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_ENEMY.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{0.f, 0.f, -88.5f});
	GetMesh()->SetRelativeRotation(FRotator{0.f, -90.f, 0.f});

	AIControllerClass = ASSEnemyBossAIController::StaticClass();
	AutoPossessAI     = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASSEnemyBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSEnemyBossCharacter::StopAI()
{
	Super::StopAI();

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void ASSEnemyBossCharacter::RunAI()
{
	Super::RunAI();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ASSEnemyBossCharacter::BattleEntrance()
{
	ASSEnemyBossAIController* BossController = Cast<ASSEnemyBossAIController>(GetController());

	if (nullptr != BossController)
	{
		BossController->BattleEntrance();
	}

	USSEnemyBossAnimInstance* BossAnimInstance = Cast<USSEnemyBossAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr != BossAnimInstance)
	{
		BossAnimInstance->PlayBattleEntrance();
	}
}

void ASSEnemyBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(EWeaponType::Katana, GetMesh(), FName(""));
		CombatComponent->EquipDefenseBarrier();
		CombatComponent->SetEnemyWeapon();
	}
}
