// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiAnimInstance.h"
#include "SSSamuraiCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>


USSSamuraiAnimInstance::USSSamuraiAnimInstance()
{
}

void USSSamuraiAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSSamuraiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	MyCharacter = Cast<ASSSamuraiCharacter>(Pawn);
}

void USSSamuraiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(MyCharacter))
	{
		return;
	}

	Speed = MyCharacter->GetVelocity().Size();
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::SanitizeFloat(Speed));

	Direction = CalculateDirection(MyCharacter->GetVelocity(), MyCharacter->GetActorRotation());

	bIsCrouch = MyCharacter->IsCrouch();
	bIsAir = MyCharacter->GetCharacterMovement()->IsFalling();
	bIsEquip = MyCharacter->IsEquip();
	bIsDefense = MyCharacter->IsDefense();

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
