// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterAnimInstance.h"
#include "Character/SSCharacterBase.h"

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

	Speed = MyCharacter->GetVelocity().Size();
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::SanitizeFloat(Speed));

	Direction = CalculateDirection(MyCharacter->GetVelocity(), MyCharacter->GetActorRotation());
}
