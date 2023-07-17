// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_SelectRandomIndex.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API UBTD_SelectRandomIndex : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_SelectRandomIndex();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 MaxIndex;
};
