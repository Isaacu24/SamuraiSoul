// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSAI.h"

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

	AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASSEnemyAIController::TargetPerceptionUpdated);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
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
		AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	}

	RunAI();

	SetPatrol(true);
}

void ASSEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_TARGETLOCATION, GetPawn()->GetActorLocation());

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

void ASSEnemyAIController::SetParry(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISPARRY, Value);
	}
}

void ASSEnemyAIController::SetPatrol(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISPATROL, Value);
	}
}

void ASSEnemyAIController::SetEquip(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISEQUIP, Value);
	}
}

void ASSEnemyAIController::SetHit(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISHIT, Value);
	}
}

void ASSEnemyAIController::SetDead(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISDEAD, Value);
	}
}

void ASSEnemyAIController::SetRebound(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISREBOUND, Value);
	}
}

void ASSEnemyAIController::SetBeExecuted(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISBEEXECUTED, Value);
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
			bool IsDetected = Stimulus.WasSuccessfullySensed();

			Blackboard->SetValueAsBool(BBKEY_ISSEEPLAYER, IsDetected);

			//플레이어 목격 시 순찰 정지.
			if (true == IsDetected)
			{
				SetPatrol(false);
			}
		}
	}
}
