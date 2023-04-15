// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SSEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USSEnemyAnimInstance();

	void PlayHitMontage();
	void PlayDeathMontage();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeathMontage;
};