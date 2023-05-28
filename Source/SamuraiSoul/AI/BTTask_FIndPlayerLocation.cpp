// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FIndPlayerLocation.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FIndPlayerLocation::UBTTask_FIndPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FIndPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (nullptr == Player)
	{
		return EBTNodeResult::Failed;
	}

	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetAIOwner());
	FVector PlayerLocation           = Player->GetActorLocation();

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(Controller->GetPawn());

	if (true == SearchRandom)
	{
		FNavLocation NavLocation = {};

		UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		if (nullptr != NaviSystem
			&& NaviSystem->GetRandomPointInNavigableRadius(PlayerLocation, AIPawn->GetAIPatrolRadius(), NavLocation, nullptr))
		{
			Controller->GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), NavLocation);
		}
	}

	else
	{
		Controller->GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), PlayerLocation);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
