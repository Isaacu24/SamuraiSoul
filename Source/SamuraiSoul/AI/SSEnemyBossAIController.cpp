// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyBossAIController.h"

#include "SSAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

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

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASSEnemyBossAIController::TargetPerceptionUpdated);
}

void ASSEnemyBossAIController::TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
}

void ASSEnemyBossAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
