// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterAnimInstance.h"
#include "Character/SSCharacterBase.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/CapsuleComponent.h"

USSCharacterAnimInstance::USSCharacterAnimInstance()
{
}

void USSCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	MyCharacter = Cast<ASSCharacterBase>(Pawn);
}

void USSCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(MyCharacter))
	{
		return;
	}

	Speed     = MyCharacter->GetVelocity().Size();
	Direction = CalculateDirection(MyCharacter->GetVelocity(), MyCharacter->GetActorRotation());
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::SanitizeFloat(Speed));

	bPrevIsAir = bIsAir;

	bIsCrouch  = MyCharacter->IsCrouch();
	bIsAir     = MyCharacter->GetCharacterMovement()->IsFalling();
	bIsEquip   = MyCharacter->IsEquip();
	bIsDefense = MyCharacter->IsDefense();
	bIsLockOn  = MyCharacter->IsLockOn();

	if (false == bIsFristDefense)
	{
		if (true == bIsDefense)
		{
			bIsFristDefense = true;
		}
	}

	if (false == bIsDefense)
	{
		bIsFristDefense = false;
	}

	if (true == bPrevIsAir)
	{
		if (false == bIsAir)
		{
			//Landing Event. ex) Jump Aiblity Cancel
			MyCharacter->OnCharacterLanded.Broadcast();
		}
	}
}

void USSCharacterAnimInstance::AnimNotify_Ragdoll() const
{
	if (nullptr != MyCharacter)
	{
		MyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MyCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

		MyCharacter->GetCharacterMovement()->StopMovementImmediately();
		MyCharacter->GetCharacterMovement()->DisableMovement();

		MyCharacter->GetMesh()->SetSimulatePhysics(true);
		MyCharacter->GetMesh()->WakeAllRigidBodies();

		MyCharacter->GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	}
}

void USSCharacterAnimInstance::AnimNotify_Die() const
{
	if (nullptr != MyCharacter)
	{
		MyCharacter->Die();
	}
}
