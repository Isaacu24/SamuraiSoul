// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS_InAttackRange.h"

#include "SSAI.h"
#include "SSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_InAttackRange::UBTS_InAttackRange()
{
	NodeName = TEXT("InAttackRange");
}

void UBTS_InAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn           = OwnerComp.GetAIOwner()->GetPawn();
	ASSEnemyAIController* Controller = Cast<ASSEnemyAIController>(OwnerComp.GetOwner());

	if (nullptr == ControllingPawn)
	{
		return;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));

	if (nullptr == Target)
	{
		return;
	}

	float DistanceToTarget      = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();

	if (AttackRangeWithRadius >= DistanceToTarget)
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_INATTACKRANGE, true);
	}

	else
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(BBKEY_INATTACKRANGE, false);
	}

	//bool bResult = (DistanceToTarget <= AttackRangeWithRadius);

	//if (500.f <= DistanceToTarget)
	//{
	//	AIPawn->Run();
	//}

	//else
	//{
	//	AIPawn->Walk();
	//}
}
