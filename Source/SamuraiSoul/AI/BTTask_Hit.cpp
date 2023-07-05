// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_Hit.h"
#include "AbilitySystemComponent.h"
#include "SSEnemyBaseAIController.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"
#include "SSGameplayTags.h"

UBTTask_Hit::UBTTask_Hit()
{
	bNotifyTick = true;

	NodeName = TEXT("Hit");
}

EBTNodeResult::Type UBTTask_Hit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AbilitySystem = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());

	return EBTNodeResult::InProgress;
}

void UBTTask_Hit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (nullptr == AbilitySystem)
	{
		return;
	}

	bool IsHit = AbilitySystem->GetAbilitySystemComponent()->HasMatchingGameplayTag(FSSGameplayTags::Get().HitTag);

	if (false == IsHit)
	{
		ASSEnemyBaseAIController* Controller = Cast<ASSEnemyBaseAIController>(OwnerComp.GetAIOwner());
		Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_ISHIT, IsHit);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
