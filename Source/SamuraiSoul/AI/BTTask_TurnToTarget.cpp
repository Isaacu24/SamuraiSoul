// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "AI/SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName    = TEXT("Turn");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetLocation")));
	if (nullptr == TargetPawn)
	{
		return EBTNodeResult::Failed;
	}

	AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z       = 0.0f;
	TargetRot          = FRotationMatrix::MakeFromX(LookVector).Rotator();

	return EBTNodeResult::InProgress;
}

void UBTTask_TurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const float TurnSpeed = AIPawn->GetAITurnSpeed();
	ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed));

	if (KINDA_SMALL_NUMBER >= ControllingPawn->GetActorRotation().Yaw - TargetRot.Yaw)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
