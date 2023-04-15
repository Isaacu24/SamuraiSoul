// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "SSEnemyCharacter.generated.h"

class UGameplayEffect;

DECLARE_DELEGATE(FAnimDelegate);

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyCharacter : public ASSEnemyCharacterBase
{
	GENERATED_BODY()

public:
	ASSEnemyCharacter();

	void DamageCheck();

	FAnimDelegate HitDelegate;
	FAnimDelegate DeathDelegate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DamageEffect;
};
