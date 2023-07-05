// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_EquipUnarm.h"
#include "AIController.h"
#include "SSAI.h"
#include "SSEnemyBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Interface/SSBehaviorInterface.h"

UBTTask_EquipUnarm::UBTTask_EquipUnarm()
{
	NodeName = TEXT("EquipUnarm");
}

EBTNodeResult::Type UBTTask_EquipUnarm::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn                      = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyBaseAIController* EnemyAIController = Cast<ASSEnemyBaseAIController>(ControllingPawn->GetController());
	EnemyAIController->SetFocus(nullptr);

	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(ControllingPawn);

	if (nullptr == BehaviorPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAbilityFinished OnEquipUnarmFinished;

	OnEquipUnarmFinished.BindLambda(
	                                [&]()
	                                {
		                                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	                                });

	AIPawn->SetAIEquipUnarmDelegate(OnEquipUnarmFinished);
	AIPawn->EquipUnarm();

	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(BBKEY_ISEQUIP, BehaviorPawn->IsEquip());

	return EBTNodeResult::InProgress;
}
