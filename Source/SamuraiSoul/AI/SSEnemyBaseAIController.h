// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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

	UFUNCTION()
	void TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus);

	void RunAI();
	void StopAI();

	void SetParry(bool Value);

	void SetPatrol(bool Value);
	void SetEquip(bool Value);

	void SetHit(bool Value);
	void SetDead(bool Value);
	void SetRebound(bool Value);
	void SetBeExecuted(bool Value);

	UAIPerceptionComponent* GetAIPerceptionComponent() const
	{
		return AIPerceptionComponent;
	}

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
	TObjectPtr<UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<UBehaviorTree> BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfigSight     = nullptr;
	TObjectPtr<UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;

	bool PrevIsDetected;
};
