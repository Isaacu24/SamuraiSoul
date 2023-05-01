// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
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
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

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

	CombatComponent->HitEvent.BindUObject(this, &ASSEnemyCharacter::HitEvent);

	bIsLog = false;
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

void ASSEnemyCharacter::AttackEvent()
{

}

void ASSEnemyCharacter::HitEvent()
{
	if (0.f >= Attributes->GetHealth())
	{
		return;
	}

	if (nullptr != AbilitySystemComponent)
	{
		HitDelegate.Execute();
		UE_LOG(LogTemp, Log, TEXT("Enemy HP: %f"), Attributes->GetHealth());

			//if (0.f >= Attributes->GetHealth())
			//{
			//	DeathDelegate.Execute();

			//	USkeletalMeshComponent* MyMesh = GetMesh();

			//	if (!MyMesh)
			//		return;

			//	MyMesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));

			//	MyMesh->SetSimulatePhysics(true);
			//	MyMesh->WakeAllRigidBodies();

			//	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			//	//SetMovementMode(EMovementMode::MOVE_None);

			//	MyMesh->AddImpulse((GetVelocity() / 2.f)* MyMesh->GetMass());
			//	MyMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
			//}
	}
}
