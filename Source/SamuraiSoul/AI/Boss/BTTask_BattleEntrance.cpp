// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Boss/BTTask_BattleEntrance.h"

UBTTask_BattleEntrance::UBTTask_BattleEntrance()
{
	NodeName = TEXT("Battle Entrance");
}

EBTNodeResult::Type UBTTask_BattleEntrance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
