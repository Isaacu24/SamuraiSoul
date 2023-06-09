// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SSWolfAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSWolfAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USSWolfAnimInstance();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
