// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "SSAI.h"
#include "SSEnemyAIController.h"
#include "Interface/SSCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn                  = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyAIController* EnemyAIController = Cast<ASSEnemyAIController>(ControllingPawn->GetController());
	EnemyAIController->SetFocus(nullptr);

	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAbilityFinished OnAttackFinished;

	OnAttackFinished.BindLambda(
	                            [&]()
	                            {
		                            ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetOwner());
		                            Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_INATTACKRANGE, false);
		                            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	                            });

	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->AttackByAI();

	return EBTNodeResult::InProgress;
}
