// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SSSamuraiAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSSamuraiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USSSamuraiAnimInstance();

	//다음 어택 몽타주로 이동
	FName GetAttackMontageSectionName(int32 Section);
	void JumpToAttackMontageSection(int32 NewSection, UAnimMontage* Montage);

	UFUNCTION()
	void AnimNotify_NextSlashCheck();

	FOnNextAttackCheckDelegate OnNextAttackCheck;

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<class ASSSamuraiCharacter> MyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	float Direction = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	bool bIsCrouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	bool bIsAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	bool bIsEquip = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool bIsDefense = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool bIsFristDefense = false;
};
