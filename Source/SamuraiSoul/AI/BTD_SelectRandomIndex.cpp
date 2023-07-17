// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTD_SelectRandomIndex.h"
#include "SSEnemyBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"

UBTD_SelectRandomIndex::UBTD_SelectRandomIndex()
{
	NodeName = TEXT("Select RandomAttack");
}

bool UBTD_SelectRandomIndex::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	int Result = FMath::RandRange(0, MaxIndex);

	ASSEnemyBaseAIController* Controller = Cast<ASSEnemyBaseAIController>(OwnerComp.GetOwner());
	Controller->GetBlackboardComponent()->SetValueAsInt(BBKEY_RANDOMINDEX, Result);

	return true;
}
