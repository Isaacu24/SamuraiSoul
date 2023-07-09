// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Defense.h"
#include "SSAI.h"
#include "SSEnemyBaseAIController.h"
#include "Interface/SSCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Defense::UBTTask_Defense()
{
	NodeName = TEXT("Defense");
}

EBTNodeResult::Type UBTTask_Defense::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn                      = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyBaseAIController* EnemyAIController = Cast<ASSEnemyBaseAIController>(ControllingPawn->GetController());
	UObject* TargetObject                       = EnemyAIController->GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET);
	AActor* PlayerActor                         = Cast<AActor>(TargetObject);

	EnemyAIController->SetFocus(PlayerActor);
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(BBKEY_ISDEFENSE, true);

	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAbilityFinished OnDefenseFinished;

	OnDefenseFinished.BindLambda(
	                             [&]()
	                             {
		                             ASSEnemyBaseAIController* Controller = Cast<ASSEnemyBaseAIController>(OwnerComp.GetOwner());
		                             Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_ISDEFENSE, false);

		                             FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	                             });

	AIPawn->SetAIDefenseDelegate(OnDefenseFinished);
	AIPawn->DefenseByAI();

	return EBTNodeResult::InProgress;
}
