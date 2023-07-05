// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/SSAnimNotifyState_Dead.h"
#include "Character/SSCharacterBase.h"
#include <Components/CapsuleComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

USSAnimNotifyState_Dead::USSAnimNotifyState_Dead()
{
}

void USSAnimNotifyState_Dead::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                          const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);;
}

void USSAnimNotifyState_Dead::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                         const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void USSAnimNotifyState_Dead::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
