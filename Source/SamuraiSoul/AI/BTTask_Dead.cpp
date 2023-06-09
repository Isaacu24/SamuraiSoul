// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Dead.h"
#include "SSEnemyBaseAIController.h"

UBTTask_Dead::UBTTask_Dead()
{
	NodeName = TEXT("Dead");
}

EBTNodeResult::Type UBTTask_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn                      = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyBaseAIController* EnemyAIController = Cast<ASSEnemyBaseAIController>(ControllingPawn->GetController());
	EnemyAIController->SetFocus(nullptr);
	EnemyAIController->StopAI();

	return EBTNodeResult::InProgress;
}
