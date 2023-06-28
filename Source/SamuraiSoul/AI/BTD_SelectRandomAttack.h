// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_SelectRandomAttack.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTD_SelectRandomAttack : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_SelectRandomAttack();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 AttackCount;
};
