// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SpectialAttack.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "SSAI.h"
#include "SSEnemyBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SSAttributeSet.h"

UBTTask_SpectialAttack::UBTTask_SpectialAttack()
{
	NodeName = TEXT("SpectialAttack");
}

EBTNodeResult::Type UBTTask_SpectialAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn                      = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyBaseAIController* EnemyAIController = Cast<ASSEnemyBaseAIController>(ControllingPawn->GetController());
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

	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(ControllingPawn);
	const USSAttributeSet* AttributeSet  = Cast<USSAttributeSet>(AbilityPawn->GetAbilitySystemComponent()->GetAttributeSet(USSAttributeSet::StaticClass()));

	if (AttributeSet->GetMaxBalance() - 0.01f <= AttributeSet->GetBalance())
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAbilityFinished OnAttackFinished;

	OnAttackFinished.BindLambda(
	                            [&]()
	                            {
		                            ASSEnemyBaseAIController* Controller = Cast<ASSEnemyBaseAIController>(OwnerComp.GetOwner());
		                            Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_INATTACKRANGE, false);
		                            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	                            });

	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->SpectialAttackByAI(SpectialAttackTag);

	return EBTNodeResult::InProgress;
}
