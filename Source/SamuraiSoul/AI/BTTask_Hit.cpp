// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_Hit.h"
#include "AbilitySystemComponent.h"
#include "SSEnemyAIController.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"

UBTTask_Hit::UBTTask_Hit()
{
	HitTag = FGameplayTag::RequestGameplayTag(TEXT("State.Hit"));
}

EBTNodeResult::Type UBTTask_Hit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
	bool IsHit                             = AbilitySystem->GetAbilitySystemComponent()->HasMatchingGameplayTag(HitTag);

	if (true == IsHit)
	{
		return EBTNodeResult::InProgress;
	}

	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetAIOwner());
	Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_TARGETLOCATION, IsHit);

	return EBTNodeResult::Succeeded;
}
