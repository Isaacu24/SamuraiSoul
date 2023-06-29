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

	////���� �޺��� �ִٸ� ȸ���� �ϰ�
	//if (true == CombatPawn->GetHasNextComboCommand())
	//{
	//	CombatPawn->SetHasNextComboCommand(false);
	//	//Rotate?
	//}

	////���� �޺��� ���ٸ� ȸ���� �ƴ� ĵ��.
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

	////�� �Լ��� ������ �޾Ƽ� ȸ������.
	//BehaviorPawn->GetMovementVector();
}

void USSAnimNotifyState_ReceiveInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	//MeshComp->GetAnimInstance()->RootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;
}
