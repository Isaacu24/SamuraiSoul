// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SSAnimNotifyState_ReceiveInput.h"
#include "Interface/SSBehaviorInterface.h"
#include "Interface/SSCombatableInterface.h"

USSAnimNotifyState_ReceiveInput::USSAnimNotifyState_ReceiveInput()
{
}

void USSAnimNotifyState_ReceiveInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                                  const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	//MeshComp->GetAnimInstance()->RootMotionMode = ERootMotionMode::IgnoreRootMotion;

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(MeshComp->GetOwner());

	if (nullptr != BehaviorPawn)
	{
		if (true == BehaviorPawn->GetAxisInput())
		{
			MeshComp->GetAnimInstance()->Montage_Stop(0.1f);
		}
	}

	//ISSCombatableInterface* CombatPawn = Cast<ISSCombatableInterface>(MeshComp->GetOwner());

	//if (nullptr == CombatPawn)
	//{
	//	return;
	//}

	//ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(MeshComp->GetOwner());

	////다음 콤보가 있다면 회전을 하고
	//if (true == CombatPawn->GetHasNextComboCommand())
	//{
	//	CombatPawn->SetHasNextComboCommand(false);
	//	//Rotate?
	//}

	////다음 콤보가 없다면 회전이 아닌 캔슬.
	//else
	//{
	//	if (nullptr != BehaviorPawn)
	//	{
	//		if (true == BehaviorPawn->GetAxisInput())
	//		{
	//			MeshComp->GetAnimInstance()->Montage_Stop(0.1f);
	//		}
	//	}
	//}

	////이 함수로 방향을 받아서 회전하자.
	//BehaviorPawn->GetMovementVector();
}

void USSAnimNotifyState_ReceiveInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	//MeshComp->GetAnimInstance()->RootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;
}
