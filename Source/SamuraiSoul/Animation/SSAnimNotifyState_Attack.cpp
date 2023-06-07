// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAnimNotifyState_Attack.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatableInterface.h"

USSAnimNotifyState_Attack::USSAnimNotifyState_Attack()
{
}

void USSAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                            const FAnimNotifyEventReference& EventReference)
{
	if (nullptr == MeshComp->GetOwner())
	{
		return;
	}

	ISSCombatableInterface* Combatable = Cast<ISSCombatableInterface>(MeshComp->GetOwner());

	if (nullptr != Combatable)
	{
		Combatable->GetCombatComponent()->OnWeapon();
	}
}

void USSAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void USSAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (nullptr == MeshComp->GetOwner())
	{
		return;
	}

	ISSCombatableInterface* Combatable = Cast<ISSCombatableInterface>(MeshComp->GetOwner());

	if (nullptr != Combatable)
	{
		Combatable->GetCombatComponent()->OffWeapon();
	}
}
