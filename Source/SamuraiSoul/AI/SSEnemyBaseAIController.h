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

	UAIPerceptionComponent* GetAIPerceptionComponent() const
	{
		return AIPerceptionComponent;
	}

	virtual void SetParry(bool Value);
	virtual void SetHit(bool Value);
	virtual void SetDead(bool Value);
	virtual void SetRebound(bool Value);
	virtual void SetEquip(bool Value);
	virtual void SetBeExecuted(bool Value);

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
