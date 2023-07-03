// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterAnimInstance.h"
#include "Character/SSCharacterBase.h"
#include <GameFramework/CharacterMovementComponent.h>

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

void USSCharacterAnimInstance::AnimNofify_Ragdoll()
{
	if (nullptr != MyCharacter)
	{
		MyCharacter->GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	}
}
