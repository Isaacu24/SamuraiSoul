// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTDecorator_AttackInRange.h"
#include "BTDecorator_AttackInRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SSCharacterAIInterface.h"


UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (nullptr == Target)
	{
		return false;
	}

	const float DistanceToTarget      = ControllingPawn->GetDistanceTo(Target);
	const float AttackRangeWithRadius = AIPawn->GetAIAttackRange();

	bResult = (DistanceToTarget <= AttackRangeWithRadius);

	return bResult;
}
