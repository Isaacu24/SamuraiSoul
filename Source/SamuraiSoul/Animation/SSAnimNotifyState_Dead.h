// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SSAnimNotifyState_Dead.generated.h"

class ASSCharacterBase;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAnimNotifyState_Dead : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	USSAnimNotifyState_Dead();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	                        const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY()
	ASSCharacterBase* OwnerCharacter;
};
