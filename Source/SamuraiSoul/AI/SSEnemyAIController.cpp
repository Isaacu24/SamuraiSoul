// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SSEnemyAIController.h"
#include "SSAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Hearing.h"
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

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	AISenseConfigSight    = CreateDefaultSubobject<UAISenseConfig_Sight>("Sense_Sight");
	AISenseConfigHearing  = CreateDefaultSubobject<UAISenseConfig_Hearing>("Sense_Hearing");

	AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
	AIPerceptionComponent->SetDominantSense(AISenseConfigHearing->GetSenseImplementation());

	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASSEnemyAIController::TargetPerceptionUpdated);
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ASSEnemyAIController::PerceptionUpdated);
}

void ASSEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(InPawn);

	////Sight
	if (nullptr != AIPawn
		&& nullptr != AISenseConfigSight)
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

	//Hearing
	if (nullptr != AIPawn
		&& nullptr != AISenseConfigHearing)
	{
		AISenseConfigHearing->HearingRange                             = AIPawn->GetAIHearingRange();
		AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies    = true;
		AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;
		AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals   = true;
		AISenseConfigHearing->SetMaxAge(5.0f);

		AIPerceptionComponent->SetDominantSense(AISenseConfigHearing->GetSenseImplementation());
		AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);
	}

	SetPatrol(AIPawn->GetAIIsStartPatrol());
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

void ASSEnemyAIController::SetBeExecuted(bool Value)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	if (true == UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsBool(BBKEY_ISBEEXECUTED, Value);
	}
}

void ASSEnemyAIController::SetRebound(bool Value)
{
	Super::SetRebound(Value);
}

void ASSEnemyAIController::TargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
	ASSCharacterBase* InCharacter = Cast<ASSCharacterBase>(InActor);

	if (nullptr == InCharacter
		|| true == InCharacter->IsDie())
	{
		return;
	}

	if (nullptr != InCharacter->GetController()
		&& true == InCharacter->GetController()->IsPlayerController())
	{
		UBlackboardComponent* BlackboardPtr = Blackboard.Get();

		if (false == UseBlackboard(BBAsset, BlackboardPtr))
		{
			return;
		}

		const bool IsDetected = Stimulus.WasSuccessfullySensed();
		Blackboard->SetValueAsBool(BBKEY_ISSEEPLAYER, IsDetected);

		//플레이어 목격 시 순찰 정지.
		if (true == IsDetected
			&& false == PrevIsDetected)
		{
			AISenseConfigSight->PeripheralVisionAngleDegrees = 180.f;

			AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
			AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);

			SetFocus(InCharacter);
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

			SetFocus(nullptr);
			SetPatrol(true);
			AIPawn->Walk();
		}

		PrevIsDetected = IsDetected;
	}
}

void ASSEnemyAIController::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (size_t i = 0; i < UpdatedActors.Num(); ++i)
	{
		FActorPerceptionBlueprintInfo Info;
		GetPerceptionComponent()->GetActorsPerception(UpdatedActors[i], Info);

		for (size_t j = 0; j < Info.LastSensedStimuli.Num(); ++j)
		{
			FAIStimulus const Stimulus = Info.LastSensedStimuli[j];

			if (AITAG_NOISE == Stimulus.Tag)
			{
				const bool IsDetected = Stimulus.WasSuccessfullySensed();
				Blackboard->SetValueAsBool(BBKEY_ISSEEPLAYER, IsDetected);
			}
		}
	}
}
