// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EquipUnarm.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTTask_EquipUnarm : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_EquipUnarm();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
};
