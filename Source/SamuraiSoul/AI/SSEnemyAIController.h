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

	virtual void SetParry(bool Value) override;

	void SetPatrol(bool Value);
	virtual void SetEquip(bool Value) override;

	virtual void SetHit(bool Value) override;
	virtual void SetDead(bool Value) override;
	virtual void SetRebound(bool Value) override;
	virtual void SetBeExecuted(bool Value) override;
};
