// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "../Animation/SSEnemyAnimInstance.h"
#include "../Abilities/SSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

ASSEnemyCharacter::ASSEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/MyContent/Mesh/Enemy/Samurai/SK_EnemySamurai_Katana.SK_EnemySamurai_Katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/AI/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -89.f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });
}

void ASSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StabTime += DeltaTime;

	if (10.f <= StabTime
		&& 0.f < Attributes->GetHealth())
	{
		StabTime = 0.f;
		StabDelegate.Execute();
	}
}
