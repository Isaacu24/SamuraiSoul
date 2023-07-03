// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SSEnemyBaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSAI.h"
#include "Kismet/GameplayStatics.h"

ASSEnemyBaseAIController::ASSEnemyBaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	AISenseConfigSight    = CreateDefaultSubobject<UAISenseConfig_Sight>("Sense_Sight");
	AISenseConfigHearing  = CreateDefaultSubobject<UAISenseConfig_Hearing>("Sense_Hearing");

	AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());
	AIPerceptionComponent->SetDominantSense(AISenseConfigHearing->GetSenseImplementation());

	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);
}

void ASSEnemyBaseAIController::OnPossess(APawn* InPawn)
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
		Blackboard->SetValueAsObject(BBKEY_TARGET, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

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
}

void ASSEnemyBaseAIController::SetHit(bool Value)
{
}

void ASSEnemyBaseAIController::SetDead(bool Value)
{
}

void ASSEnemyBaseAIController::SetRebound(bool Value)
{
}

void ASSEnemyBaseAIController::SetEquip(bool Value)
{
}

void ASSEnemyBaseAIController::SetBeExecuted(bool Value)
{
}
