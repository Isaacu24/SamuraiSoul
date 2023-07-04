// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterAnimInstance.h"
#include "SSSamuraiAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSSamuraiAnimInstance : public USSCharacterAnimInstance
{
	GENERATED_BODY()

public:
	USSSamuraiAnimInstance();

	//���� ���� ��Ÿ�ַ� �̵�
	FName GetAttackMontageSectionName(int32 Section);
	void JumpToAttackMontageSection(int32 NewSection, UAnimMontage* Montage);

	UFUNCTION()
	void AnimNotify_NextSlashCheck() const;

	UFUNCTION()
	void AnimNotify_Footstep() const;

	FOnNextAttackCheckDelegate OnNextAttackCheck;

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
};
