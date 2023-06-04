// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChasePlayer.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSAI.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetOwner());
	FVector PalyerLocation           = Controller->GetBlackboardComponent()->GetValueAsVector(BBKEY_TARGETLOCATION);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PalyerLocation);

	APawn* ControllingPawn          = Controller->GetPawn();
	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	const float DistanceToTarget = FVector::Distance(ControllingPawn->GetActorLocation(), PalyerLocation);

	if (200.f <= DistanceToTarget)
	{
		AIPawn->Run();
	}

	else
	{
		if (100.f <= DistanceToTarget)
		{
			Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}

		AIPawn->Walk();
	}

	return EBTNodeResult::Succeeded;
}
