// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SSAnimNotifyState.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;
struct FAnimNotifyEvent;
struct FBranchingPointNotifyPayload;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	USSAnimNotifyState();

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
};
