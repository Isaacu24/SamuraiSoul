// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyBaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSAI.h"
#include "SSEnemyAIController.h"

ASSEnemyBaseAIController::ASSEnemyBaseAIController()
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
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");

	AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASSEnemyBaseAIController::TargetPerceptionUpdated);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
}

void ASSEnemyBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(InPawn);

	if (nullptr != AIPawn)
	{
		AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
		AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
		AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
		AISenseConfigSight->SightRadius = AIPawn->GetAIDetectRadius();
		AISenseConfigSight->LoseSightRadius = AIPawn->GetAILoseDetectRadius();
		AISenseConfigSight->PeripheralVisionAngleDegrees = AIPawn->GetAISight();
		AISenseConfigSight->SetMaxAge(5.0f);

		AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
		AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	}

	RunAI();

	SetPatrol(true);
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
		Blackboard->SetValueAsVector(BBKEY_TARGETLOCATION, GetPawn()->GetActorLocation());

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

void ASSEnemyBaseAIController::SetParry(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISPARRY, Value);
	}
}

void ASSEnemyBaseAIController::SetPatrol(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISPATROL, Value);
	}
}

void ASSEnemyBaseAIController::SetEquip(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISEQUIP, Value);
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

void ASSEnemyBaseAIController::SetDead(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISDEAD, Value);
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

void ASSEnemyBaseAIController::SetBeExecuted(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISBEEXECUTED, Value);
	}
}

void ASSEnemyBaseAIController::TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
	APawn* Player = Cast<APawn>(InActor);

	if (nullptr != Player
		&& true == Player->GetController()->IsPlayerController())
	{
		UBlackboardComponent* BlackboardPtr = Blackboard.Get();

		if (false == UseBlackboard(BBAsset, BlackboardPtr))
		{
			return;
		}

		bool IsDetected = Stimulus.WasSuccessfullySensed();

		Blackboard->SetValueAsBool(BBKEY_ISSEEPLAYER, IsDetected);

		//플레이어 목격 시 순찰 정지.
		if (true == IsDetected
			&& false == PrevIsDetected)
		{
			AISenseConfigSight->PeripheralVisionAngleDegrees = 180.f;

			AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
			AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);

			SetPatrol(false);
		}

		else if (false == IsDetected
			&& true == PrevIsDetected)
		{
			ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetPawn());

			if (nullptr == AIPawn)
			{
				return;
			}

			AISenseConfigSight->PeripheralVisionAngleDegrees = AIPawn->GetAISight();

			AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
			AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);

			SetPatrol(true);
			AIPawn->Walk();
		}

		PrevIsDetected = IsDetected;
	}
}
