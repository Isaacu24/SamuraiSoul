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

	UFUNCTION()
	virtual void TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus);

protected:
	virtual void OnPossess(APawn* InPawn) override;

	void SetParry(bool Value);

	void SetPatrol(bool Value);
	void SetEquip(bool Value);

	void SetHit(bool Value);
	void SetDead(bool Value);
	void SetRebound(bool Value);
	void SetBeExecuted(bool Value);
};
