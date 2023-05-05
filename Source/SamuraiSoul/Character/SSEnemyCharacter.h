// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "Game/SamuraiSoul.h"
#include "SSEnemyCharacter.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyCharacter : public ASSEnemyCharacterBase
{
	GENERATED_BODY()

public:
	ASSEnemyCharacter();

	FAnimDelegate StabDelegate;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AttackEvent(EWeaponType Type);
	void HitEvent(EWeaponType Type);

private:
	UPROPERTY()
	float StabTime;
	uint8 bIsLog : 1;
};
