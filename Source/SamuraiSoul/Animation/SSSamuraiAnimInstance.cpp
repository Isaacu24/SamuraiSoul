// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiAnimInstance.h"

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
}

void USSSamuraiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

FName USSSamuraiAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Slash%d"), Section));
}

void USSSamuraiAnimInstance::JumpToAttackMontageSection(int32 NewSection, UAnimMontage* Montage)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), Montage);
}

void USSSamuraiAnimInstance::AnimNotify_NextSlashCheck() const
{
	OnNextAttackCheck.Broadcast();
}
