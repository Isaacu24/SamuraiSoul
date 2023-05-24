// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTTask_RandomMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()	

public:
	UBTTask_RandomMove();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
	float SearchReadius;

};
