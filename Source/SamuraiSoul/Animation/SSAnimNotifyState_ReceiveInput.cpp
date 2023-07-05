// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SSAnimNotifyState_ReceiveInput.h"
#include "Interface/SSBehaviorInterface.h"

USSAnimNotifyState_ReceiveInput::USSAnimNotifyState_ReceiveInput()
{
}

void USSAnimNotifyState_ReceiveInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                                  const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	BehaviorPawn = Cast<ISSBehaviorInterface>(MeshComp->GetOwner());

	if (nullptr != BehaviorPawn)
	{
		if (true == BehaviorPawn->GetAxisInput())
		{
			MeshComp->GetAnimInstance()->Montage_Stop(0.1f);
		}
	}
}

void USSAnimNotifyState_ReceiveInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                                 const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (nullptr != BehaviorPawn)
	{
		if (true == BehaviorPawn->GetAxisInput())
		{
			MeshComp->GetAnimInstance()->Montage_Stop(0.1f);
		}
	}
}

void USSAnimNotifyState_ReceiveInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
