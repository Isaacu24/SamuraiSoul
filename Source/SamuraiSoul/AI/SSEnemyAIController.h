// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "SSEnemyAIController.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASSEnemyAIController();

	UFUNCTION()
	void TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus);

	void RunAI();
	void StopAI();

	void ReboundAI();

	UAIPerceptionComponent* GetAIPerceptionComponent() const
	{
		return AIPerceptionComponent;
	}

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight     = nullptr;
	TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;
};
