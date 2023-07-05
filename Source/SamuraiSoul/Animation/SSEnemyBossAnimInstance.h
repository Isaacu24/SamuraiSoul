// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SSCharacterAnimInstance.h"
#include "SSEnemyBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSEnemyBossAnimInstance : public USSCharacterAnimInstance
{
	GENERATED_BODY()

public:
	USSEnemyBossAnimInstance();

	void PlayBattleEntrance();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UAnimMontage* BattleEntranceMontage;
};
