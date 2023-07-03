// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_FindRandomLocation.h"
#include "SSEnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetAIOwner());

	if (nullptr == Controller)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Enemy = Controller->GetPawn();

	if (nullptr == Enemy)
	{
		return EBTNodeResult::Failed;
	}

	const FVector Origin     = Enemy->GetActorLocation();
	FNavLocation NavLocation = {};

	const UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	//SearchReadius?
	if (nullptr != NaviSystem
		&& true == NaviSystem->GetRandomPointInNavigableRadius(Origin, SearchReadius, NavLocation))
	{
		Controller->GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NavLocation);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
