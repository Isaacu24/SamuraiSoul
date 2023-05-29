// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "Interface/SSCharacterAIInterface.h"

ASSEnemyAIController::ASSEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BB_ASSET(TEXT("/Script/AIModule.BlackboardData'/Game/MyContent/AI/Enemy/BB_EnemyCharacter.BB_EnemyCharacter'"));

	if (nullptr != BB_ASSET.Object)
	{
		BBAsset = BB_ASSET.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BT_ASSET(TEXT("/Script/AIModule.BehaviorTree'/Game/MyContent/AI/Enemy/BT_EnemyCharacter.BT_EnemyCharacter'"));

	if (nullptr != BT_ASSET.Object)
	{
		BTAsset = BT_ASSET.Object;
	}

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	AISenseConfigSight    = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
}

void ASSEnemyAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("HomePos"), GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void ASSEnemyAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (nullptr != BTComponent)
	{
		BTComponent->StopTree();
	}
}

void ASSEnemyAIController::ReboundAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("IsRebound"), GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void ASSEnemyAIController::TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
	APawn* Player = Cast<APawn>(InActor);

	if (nullptr != Player
		&& true == Player->GetController()->IsPlayerController())
	{
		UBlackboardComponent* BlackboardPtr = Blackboard.Get();

		if (true == UseBlackboard(BBAsset, BlackboardPtr))
		{
			Blackboard->SetValueAsBool(TEXT("IsSeePlayer"), Stimulus.WasSuccessfullySensed());
		}
	}
}

void ASSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(InPawn);

	if (nullptr != AIPawn)
	{
		AISenseConfigSight->DetectionByAffiliation.bDetectEnemies    = true;
		AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
		AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals   = true;
		AISenseConfigSight->SightRadius                              = AIPawn->GetAIDetectRadius();
		AISenseConfigSight->LoseSightRadius                          = AIPawn->GetAILoseDetectRadius();
		AISenseConfigSight->PeripheralVisionAngleDegrees             = AIPawn->GetAISight();
		AISenseConfigSight->SetMaxAge(5.0f);

		AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASSEnemyAIController::TargetPerceptionUpdated);
		AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	}

	RunAI();
}
