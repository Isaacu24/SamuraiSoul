// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SSAnimNotifyState_SlowTime.h"


void USSAnimNotifyState_SlowTime::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                              const FAnimNotifyEventReference& EventReference)
{
	if (nullptr != MeshComp->GetOwner())
	{
		MeshComp->GetOwner()->GetWorldSettings()->SetTimeDilation(0.25f);
	}
}

void USSAnimNotifyState_SlowTime::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                             const FAnimNotifyEventReference& EventReference)
{
}

void USSAnimNotifyState_SlowTime::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (nullptr != MeshComp->GetOwner())
	{
		MeshComp->GetOwner()->GetWorldSettings()->SetTimeDilation(1.f);
	}
}
