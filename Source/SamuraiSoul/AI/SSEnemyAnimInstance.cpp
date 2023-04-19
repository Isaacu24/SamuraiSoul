// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyAnimInstance.h"
#include "SSEnemyCharacter.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

USSEnemyAnimInstance::USSEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Hit.AM_Hit'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Death.AM_Death'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> STAB_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Stab.AM_Stab'"));

	if (true == HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}

	if (true == DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
	}

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

	APawn* Pawn = TryGetPawnOwner();

	if (false == IsValid(Pawn))
	{
		return;
	}

	ASSEnemyCharacter* MyCharacter = Cast<ASSEnemyCharacter>(Pawn);

	if (true == IsValid(MyCharacter))
	{
		MyCharacter->HitDelegate.BindUObject(this, &USSEnemyAnimInstance::PlayHitMontage);
		MyCharacter->DeathDelegate.BindUObject(this, &USSEnemyAnimInstance::PlayDeathMontage);
		MyCharacter->StabDelegate.BindUObject(this, &USSEnemyAnimInstance::PlayStabMontage);
	}
}

void USSEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void USSEnemyAnimInstance::PlayHitMontage()
{
	Montage_Play(HitMontage, 1.0f);
}

void USSEnemyAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
}

void USSEnemyAnimInstance::AnimNotify_RagdollDeath()
{
	APawn* Pawn = TryGetPawnOwner();

	if (false == IsValid(Pawn))
	{
		return;
	}

	ASSEnemyCharacter* MyCharacter = Cast<ASSEnemyCharacter>(Pawn);
	USkeletalMeshComponent* MyMesh = MyCharacter->GetMesh();

	if (!MyMesh)
		return;

	MyMesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));

	MyMesh->SetSimulatePhysics(true);
	MyMesh->WakeAllRigidBodies();

	MyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
