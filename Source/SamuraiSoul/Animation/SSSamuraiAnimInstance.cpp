// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiAnimInstance.h"
#include "Character/SSCharacterBase.h"
#include "Perception/AISenseConfig_Hearing.h"

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

void USSSamuraiAnimInstance::AnimNotify_Footstep() const
{
	if (nullptr != MyCharacter)
	{
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), MyCharacter->GetActorLocation(), 1.0f, MyCharacter, 0.0f, FName("Run"));
	}
}
