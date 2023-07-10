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

	UFUNCTION()
	virtual void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UAIPerceptionComponent* GetAIPerceptionComponent() const
	{
		return AIPerceptionComponent;
	}

	virtual void SetParry(bool Value);
	virtual void SetPatrol(bool Value);
	virtual void SetHit(bool Value);
	virtual void SetDead(bool Value);
	virtual void SetEquip(bool Value);
	virtual void SetBeExecuted(bool Value);

	virtual void SetRebound(bool Value) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfigSight;

	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<UAISenseConfig_Hearing> AISenseConfigHearing;
};
