// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSUserWidget.h"
#include "SSBalanceGaugeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSBalanceGaugeWidget : public USSUserWidget
{
	GENERATED_BODY()

public:
	USSBalanceGaugeWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateBPGauge(float NewCurrentBP) const;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> Gauge;

	//Balance Point.
	UPROPERTY()
	float MaxBP;
};
