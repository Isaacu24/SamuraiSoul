// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Boss/BTTask_BattleEntrance.h"
#include "AI/SSAI.h"
#include "AI/SSEnemyBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/SSEnemyBossCharacter.h"

UBTTask_BattleEntrance::UBTTask_BattleEntrance()
{
	NodeName = TEXT("Battle Entrance");
}

EBTNodeResult::Type UBTTask_BattleEntrance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn                      = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyBaseAIController* EnemyAIController = Cast<ASSEnemyBaseAIController>(ControllingPawn->GetController());

	ASSEnemyBossCharacter* Boss = Cast<ASSEnemyBossCharacter>(EnemyAIController->GetPawn());

	if (nullptr == Boss)
	{
		return EBTNodeResult::Failed;
	}

	Boss->OnBattleEtranced.AddLambda(
	                                 [&]()
	                                 {
		                                 ASSEnemyBaseAIController* Controller = Cast<ASSEnemyBaseAIController>(OwnerComp.GetOwner());
		                                 Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_ISBATTLESTART, false);
		                                 FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	                                 });

	return EBTNodeResult::InProgress;
}
