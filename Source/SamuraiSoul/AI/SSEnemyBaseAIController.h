// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character/SSEnemyCharacterBase.h"
#include "SSEnemyBaseAIController.generated.h"

class UBlackboardData;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyBaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASSEnemyBaseAIController();

	virtual void BeginPlay() override;

	void RunAI();
	void StopAI();

	virtual void SetRebound(bool Value);

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
	TObjectPtr<UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<UBehaviorTree> BTAsset;

	bool PrevIsDetected;
};
