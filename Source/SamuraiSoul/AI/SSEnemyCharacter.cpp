// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "SSEnemyAnimInstance.h"

ASSEnemyCharacter::ASSEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/MyContent/Mesh/Enemy/Samurai/SK_EnemySamurai_Katana.SK_EnemySamurai_Katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Player/Enemy/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -87.5f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });
}
