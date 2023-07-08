// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSEnemyBaseAIController.h"
#include "SSEnemyBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyBossAIController : public ASSEnemyBaseAIController
{
	GENERATED_BODY()

public:
	ASSEnemyBossAIController();

	UFUNCTION()
	virtual void TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus);

	virtual void BeginPlay() override;

	virtual void BattleEntrance();

	virtual void SetDistanceToTarget(float Value);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
