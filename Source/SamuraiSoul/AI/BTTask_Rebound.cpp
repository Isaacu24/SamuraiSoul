// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Rebound.h"

UBTTask_Rebound::UBTTask_Rebound()
{
	NodeName = TEXT("Rebound");
}

EBTNodeResult::Type UBTTask_Rebound::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
