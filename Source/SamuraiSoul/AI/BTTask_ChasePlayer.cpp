// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChasePlayer.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSAI.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetOwner());
	UObject* TargetObject            = Controller->GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET);
	AActor* PlayerActor              = Cast<AActor>(TargetObject);

	Controller->SetFocus(PlayerActor);

	//const float DistanceToTarget = FVector::Distance(ControllingPawn->GetActorLocation(), PlayerActor->GetActorLocation());

	//if (500.f <= DistanceToTarget)
	//{
	//	AIPawn->Run();
	//}

	//else
	//{
	//	AIPawn->Walk();

	//	if (AIPawn->GetAIAttackRange() >= DistanceToTarget)
	//	{
	//		Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_INATTACKRANGE, true);
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//		return EBTNodeResult::Succeeded;
	//	}
	//}

	return EBTNodeResult::Succeeded;
}
