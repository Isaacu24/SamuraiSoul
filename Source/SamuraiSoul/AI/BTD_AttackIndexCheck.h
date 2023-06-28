// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_AttackIndexCheck.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTD_AttackIndexCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_AttackIndexCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 MyIndex;
};
