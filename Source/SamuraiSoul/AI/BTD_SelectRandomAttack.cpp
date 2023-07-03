// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTD_SelectRandomAttack.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"

UBTD_SelectRandomAttack::UBTD_SelectRandomAttack()
{
	NodeName = TEXT("Select RandomAttack");
}

bool UBTD_SelectRandomAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	int Result = FMath::RandRange(0, AttackCount);
	UE_LOG(LogTemp, Error, TEXT("AttackIndex : %d"), Result);

	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetOwner());
	Controller->GetBlackboardComponent()->SetValueAsInt(BBKEY_ATTACKINDEX, Result);

	return true;
}
