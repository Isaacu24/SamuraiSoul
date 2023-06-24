// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyAIController.h"
#include "SSAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

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

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASSEnemyAIController::TargetPerceptionUpdated);
}

void ASSEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetPatrol(true);
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
		&& nullptr != Player->GetController()
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
