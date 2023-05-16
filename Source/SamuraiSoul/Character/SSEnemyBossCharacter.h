// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacterBase.h"
#include "SSEnemyBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyBossCharacter : public ASSCharacterBase
{
	GENERATED_BODY()

public:
	ASSEnemyBossCharacter();

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void SetCharacterControlData(const USSCharacterControlData* ControlData);


};
