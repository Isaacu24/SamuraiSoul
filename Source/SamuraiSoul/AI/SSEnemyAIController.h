// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSEnemyBaseAIController.h"
#include "SSEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyAIController : public ASSEnemyBaseAIController
{
	GENERATED_BODY()

public:
	ASSEnemyAIController();

	virtual void BeginPlay() override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
