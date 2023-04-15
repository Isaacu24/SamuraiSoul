// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyAnimInstance.h"
#include "SSEnemyCharacter.h"

USSEnemyAnimInstance::USSEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Hit.AM_Hit'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Death.AM_Death'"));

	if (true == HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}

	if (true == DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
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
