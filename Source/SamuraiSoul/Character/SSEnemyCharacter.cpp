// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "Game/SamuraiSoul.h"
#include "../Animation/SSEnemyAnimInstance.h"
#include "../Abilities/SSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Kismet/KismetSystemLibrary.h"
#include "Component/SSCombatComponent.h"

ASSEnemyCharacter::ASSEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/MyContent/Mesh/Enemy/Samurai/SK_EnemySamurai_Katana.SK_EnemySamurai_Katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_ENEMY(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_ENEMY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_ENEMY.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -89.f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });

	bIsLog = false;
}

void ASSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(GetMesh(), FName("Weapon_rSocket"));
		CombatComponent->EquipDefenseBarrier();
		CombatComponent->SetEnemyWeapon();
	}
}

void ASSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StabTime += DeltaTime;

	if (8.f <= StabTime
		&& false == bIsLog)
	{
		bIsLog = true;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EnemyAttacck!")));
	}

	if (10.f <= StabTime
		&& 0.f < Attributes->GetHealth())
	{
		StabTime = 0.f;
		bIsLog = false;
		StabDelegate.Execute();
	}
}

