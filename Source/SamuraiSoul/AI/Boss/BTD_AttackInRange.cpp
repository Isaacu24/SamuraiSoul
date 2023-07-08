// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Boss/BTD_AttackInRange.h"
#include "AIController.h"
#include "AI/SSAI.h"
#include "AI/SSEnemyBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"

UBTD_AttackInRange::UBTD_AttackInRange()
{
}

bool UBTD_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));

	if (nullptr == Target)
	{
		return false;
	}

	float DistanceToTarget      = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	bResult                     = (DistanceToTarget <= AttackRangeWithRadius);

	ASSEnemyBossAIController* BossController = Cast<ASSEnemyBossAIController>(OwnerComp.GetOwner());

	if (nullptr == BossController)
	{
		return false;
	}

	BossController->SetDistanceToTarget(DistanceToTarget);

	return bResult;
}
