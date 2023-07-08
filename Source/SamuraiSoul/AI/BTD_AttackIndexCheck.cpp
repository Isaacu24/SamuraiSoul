// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTD_AttackIndexCheck.h"

#include "SSAI.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_AttackIndexCheck::UBTD_AttackIndexCheck()
{
	NodeName = TEXT("AttackIndex Check");
}

bool UBTD_AttackIndexCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetOwner());
	//const int AttackIndex            = Controller->GetBlackboardComponent()->GetValueAsInt(BBKEY_ATTACKINDEX);

	//if (AttackIndex == MyIndex)
	//{
	//	return true;
	//}

	return false;
}
