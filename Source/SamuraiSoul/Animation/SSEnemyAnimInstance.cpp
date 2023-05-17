// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyAnimInstance.h"
#include "../Character/SSEnemyCharacter.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

USSEnemyAnimInstance::USSEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> STAB_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Stab.AM_Stab'"));

	if (true == STAB_MONTAGE.Succeeded())
	{
		StabMontage = STAB_MONTAGE.Object;
	}
}

void USSEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USSEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void USSEnemyAnimInstance::AnimNotify_RagdollDeath()
{
	if (false == IsValid(MyCharacter))
	{
		return;
	}

	USkeletalMeshComponent* MyMesh = MyCharacter->GetMesh();

	if (!MyMesh)
		return;

	MyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MyMesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));

	MyMesh->SetSimulatePhysics(true);
	MyMesh->WakeAllRigidBodies();

	//SetMovementMode(EMovementMode::MOVE_None);

	MyMesh->AddImpulse(MyCharacter->GetVelocity() * MyMesh->GetMass());
	MyMesh->AddRadialImpulse(MyCharacter->GetActorLocation(), 500.0f, 100.0f, ERadialImpulseFalloff::RIF_Constant, true);
}

void USSEnemyAnimInstance::AnimNotify_DeathMontageEnd()
{
	//Stop Animation
}

void USSEnemyAnimInstance::PlayStabMontage()
{
	Montage_Play(StabMontage, 1.0f);
}
