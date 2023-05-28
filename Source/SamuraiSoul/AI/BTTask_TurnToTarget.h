// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTTask_TurnToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TurnToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FRotator TargetRot;
	APawn* ControllingPawn;
	class ISSCharacterAIInterface* AIPawn;
};
