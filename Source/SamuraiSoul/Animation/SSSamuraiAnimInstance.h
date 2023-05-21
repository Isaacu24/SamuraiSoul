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

	//다음 어택 몽타주로 이동
	FName GetAttackMontageSectionName(int32 Section);
	void JumpToAttackMontageSection(int32 NewSection, UAnimMontage* Montage);

	UFUNCTION()
	void AnimNotify_NextSlashCheck() const;

	FOnNextAttackCheckDelegate OnNextAttackCheck;

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<class ASSCharacterBase> OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	uint8 bIsCrouch : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	uint8 bIsAir : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	uint8 bIsEquip : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsDefense : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsLockOn : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 bIsFristDefense : 1;
};
