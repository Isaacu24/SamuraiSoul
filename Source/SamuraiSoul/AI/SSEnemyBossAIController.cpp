// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyBossAIController.h"

#include "SSAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/SSEnemyBossCharacter.h"
#include "Perception/AIPerceptionTypes.h"

ASSEnemyBossAIController::ASSEnemyBossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BB_ASSET(TEXT("/Script/AIModule.BlackboardData'/Game/MyContent/AI/Boss/BB_EnemyBossCharacter.BB_EnemyBossCharacter'"));

	if (nullptr != BB_ASSET.Object)
	{
		BBAsset = BB_ASSET.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BT_ASSET(TEXT("/Script/AIModule.BehaviorTree'/Game/MyContent/AI/Boss/BT_EnemyBossCharacter.BT_EnemyBossCharacter'"));

	if (nullptr != BT_ASSET.Object)
	{
		BTAsset = BT_ASSET.Object;
	}
}

void ASSEnemyBossAIController::TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
}

void ASSEnemyBossAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyBossAIController::BattleEntrance()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISBATTLESTART, true);
	}
}

void ASSEnemyBossAIController::SetDistanceToTarget(float Value)
{
	ASSEnemyBossCharacter* Boss = Cast<ASSEnemyBossCharacter>(GetPawn());
	check(Boss);

	Boss->SetDistanceToTarget(Value);
}

void ASSEnemyBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
