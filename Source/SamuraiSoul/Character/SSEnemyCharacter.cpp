// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "Game/SamuraiSoul.h"
#include <Components/CapsuleComponent.h>
#include "Component/SSEnemyCombatComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "AI/SSEnemyAIController.h"

ASSEnemyCharacter::ASSEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/MyContent/Mesh/Enemy/Samurai/SK_EnemySamurai_Katana.SK_EnemySamurai_Katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		ANIM_ENEMY(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_ENEMY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_ENEMY.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{0.f, 0.f, -89.f});
	GetMesh()->SetRelativeRotation(FRotator{0.f, -90.f, 0.f});

	AIControllerClass = ASSEnemyAIController::StaticClass();
	AutoPossessAI     = EAutoPossessAI::PlacedInWorldOrSpawned;

	CombatComponent = CreateDefaultSubobject<USSEnemyCombatComponent>(TEXT("Combat Component"));

	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

void ASSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(EWeaponType::Katana, GetMesh(), FName("Weapon_rSocket"));
		CombatComponent->EquipDefenseBarrier();
		CombatComponent->SetEnemyWeapon();
	}
}

void ASSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSEnemyCharacter::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	Super::SetAIAttackDelegate(InOnAttackFinished);
}

void ASSEnemyCharacter::AttackByAI()
{
	if (nullptr != CombatComponent)
	{
		CombatComponent->AttackByAI();
	}
}
