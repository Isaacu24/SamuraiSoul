// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "Game/SamuraiSoul.h"
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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

private:
};
