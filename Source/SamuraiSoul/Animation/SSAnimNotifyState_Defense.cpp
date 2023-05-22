// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAnimNotifyState_Defense.h"
#include "Interface/SSCombatInterface.h"
#include "Component/SSCombatComponent.h"

USSAnimNotifyState_Defense::USSAnimNotifyState_Defense()
{
}

void USSAnimNotifyState_Defense::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                             const FAnimNotifyEventReference& EventReference)
{
	if (nullptr == MeshComp->GetOwner())
	{
		return;
	}

	ISSCombatInterface* Combatable = Cast<ISSCombatInterface>(MeshComp->GetOwner());

	if (nullptr != Combatable)
	{
		Combatable->GetCombatComponent()->OnDefense();
		Combatable->GetCombatComponent()->ChangeDefenseState(EDefenseState::Parry);
	}
}

void USSAnimNotifyState_Defense::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                            const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void USSAnimNotifyState_Defense::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (nullptr == MeshComp->GetOwner())
	{
		return;
	}

	ISSCombatInterface* Combatable = Cast<ISSCombatInterface>(MeshComp->GetOwner());

	if (nullptr != Combatable)
	{
		Combatable->GetCombatComponent()->ChangeDefenseState(EDefenseState::Defense);
	}
}
