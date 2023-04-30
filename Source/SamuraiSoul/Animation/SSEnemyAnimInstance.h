// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterAnimInstance.h"
#include "SSEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSEnemyAnimInstance : public USSCharacterAnimInstance
{
	GENERATED_BODY()

public:
	USSEnemyAnimInstance();

	void PlayHitMontage();
	void PlayDeathMontage();
	void PlayStabMontage();
	void PlayAttackFailMontage();

	UFUNCTION()
	void AnimNotify_RagdollDeath();

	UFUNCTION()
	void AnimNotify_DeathMontageEnd();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> StabMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> AttackFailMontage;
};