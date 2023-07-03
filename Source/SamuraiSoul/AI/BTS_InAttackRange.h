// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/BehaviorTree/BTService.h"
#include "BTS_InAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTS_InAttackRange : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_InAttackRange();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
