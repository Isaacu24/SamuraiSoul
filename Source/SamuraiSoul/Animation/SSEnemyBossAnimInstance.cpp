// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SSEnemyBossAnimInstance.h"

USSEnemyBossAnimInstance::USSEnemyBossAnimInstance()
{
}

void USSEnemyBossAnimInstance::PlayBattleEntrance()
{
	Montage_Play(BattleEntranceMontage, 1.0f);
}

void USSEnemyBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSEnemyBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USSEnemyBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
