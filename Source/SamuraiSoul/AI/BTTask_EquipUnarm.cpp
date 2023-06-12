// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_EquipUnarm.h"
#include "AIController.h"
#include "SSAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"

UBTTask_EquipUnarm::UBTTask_EquipUnarm()
{
}

EBTNodeResult::Type UBTTask_EquipUnarm::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISEQUIP, true);

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

	AIPawn->EquipUnarm();

	return EBTNodeResult::Succeeded;
}
