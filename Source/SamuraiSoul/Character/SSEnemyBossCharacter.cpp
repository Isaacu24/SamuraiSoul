// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSEnemyBossCharacter.h"

ASSEnemyBossCharacter::ASSEnemyBossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/BossyEnemy/SkeletalMesh/SK_Mannequin_UE4_WithWeapon.SK_Mannequin_UE4_WithWeapon'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_ENEMY(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyBossCharacter.AB_SSEnemyBossCharacter_C'"));
	 
	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_ENEMY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_ENEMY.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -89.f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, 0.f, -90.f });
}

void ASSEnemyBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSEnemyBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASSEnemyBossCharacter::SetCharacterControlData(const USSCharacterControlData* ControlData)
{
	Super::SetCharacterControlData(ControlData);
}