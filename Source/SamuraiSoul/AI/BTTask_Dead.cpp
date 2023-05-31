// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Dead.h"

UBTTask_Dead::UBTTask_Dead()
{
}

EBTNodeResult::Type UBTTask_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
