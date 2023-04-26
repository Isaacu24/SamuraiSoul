// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSAnimNotifyState.h"
#include "SSAnimNotifyState_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAnimNotifyState_Attack : public USSAnimNotifyState
{
	GENERATED_BODY()

public:
	USSAnimNotifyState_Attack();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY()
	uint8 bIsPlayer : 1;

	UPROPERTY()
	TSet<AActor*> ActorsToIgnore;
};
