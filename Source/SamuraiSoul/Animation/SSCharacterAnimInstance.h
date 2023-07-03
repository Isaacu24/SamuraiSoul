// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SSCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USSCharacterAnimInstance();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void AnimNofify_Ragdoll();

protected:
	UPROPERTY()
	TObjectPtr<class ASSCharacterBase> MyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Direction = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsCrouch : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsAir : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bPrevIsAir : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsEquip : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsDefense : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsLockOn : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsFristDefense : 1;
};
