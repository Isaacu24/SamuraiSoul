// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiAnimInstance.h"
#include "../Character/SSSamuraiCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

USSSamuraiAnimInstance::USSSamuraiAnimInstance()
{
	bIsCrouch = false;
	bIsAir = false;
	bIsEquip = false;
	bIsDefense = false;
	bIsFristDefense = false;
}

void USSSamuraiAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSSamuraiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USSSamuraiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(MyCharacter))
	{
		return;
	}

	OwnerCharacter = Cast<ASSSamuraiCharacter>(MyCharacter);

	Speed = MyCharacter->GetVelocity().Size();
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::SanitizeFloat(Speed));

	Direction = CalculateDirection(MyCharacter->GetVelocity(), MyCharacter->GetActorRotation());

	bIsCrouch = OwnerCharacter->IsCrouch();
	bIsAir = OwnerCharacter->GetCharacterMovement()->IsFalling();
	bIsEquip = OwnerCharacter->IsEquip();
	bIsDefense = OwnerCharacter->IsDefense();
	bIsLockOn= OwnerCharacter->IsLockOn(); // ?

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
}

FName USSSamuraiAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Slash%d"), Section));
}

void USSSamuraiAnimInstance::JumpToAttackMontageSection(int32 NewSection, UAnimMontage* Montage)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), Montage);
}

void USSSamuraiAnimInstance::AnimNotify_NextSlashCheck()
{
	OnNextAttackCheck.Broadcast();
}
