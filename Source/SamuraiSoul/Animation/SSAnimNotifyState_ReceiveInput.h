// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SSAnimNotifyState.h"
#include "SSAnimNotifyState_ReceiveInput.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAnimNotifyState_ReceiveInput : public USSAnimNotifyState
{
	GENERATED_BODY()

public:
	USSAnimNotifyState_ReceiveInput();

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
