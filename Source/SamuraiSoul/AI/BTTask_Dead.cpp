// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Dead.h"
#include "SSEnemyAIController.h"

UBTTask_Dead::UBTTask_Dead()
{
	NodeName = TEXT("Dead");
}

EBTNodeResult::Type UBTTask_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn                  = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyAIController* EnemyAIController = Cast<ASSEnemyAIController>(ControllingPawn->GetController());

	if (nullptr != EnemyAIController)
	{
		EnemyAIController->SetFocus(nullptr);
		EnemyAIController->StopAI();
	}

	return EBTNodeResult::InProgress;
}
