// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_EquipUnarm.h"
#include "AIController.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_EquipUnarm::UBTTask_EquipUnarm()
{
}

EBTNodeResult::Type UBTTask_EquipUnarm::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}


	return EBTNodeResult::InProgress;
}
