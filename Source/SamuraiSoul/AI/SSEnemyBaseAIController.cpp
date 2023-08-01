// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyBaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"
#include "Kismet/GameplayStatics.h"

ASSEnemyBaseAIController::ASSEnemyBaseAIController()
{
}

void ASSEnemyBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void ASSEnemyBaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyBaseAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		Blackboard->SetValueAsObject(BBKEY_TARGET, Player);

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void ASSEnemyBaseAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (nullptr != BTComponent)
	{
		BTComponent->StopTree();
	}
}

void ASSEnemyBaseAIController::SetRebound(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISREBOUND, Value);
	}
}

void ASSEnemyBaseAIController::SetDead(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISDEAD, Value);
	}
}

void ASSEnemyBaseAIController::SetHit(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISHIT, Value);
	}
}
