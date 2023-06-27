// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSUserWidget.h"
#include "SSBalanceWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSBalanceWidget : public USSUserWidget
{
	GENERATED_BODY()

public:
	USSBalanceWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHPBar(float NewCurrentBP) const;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> Gauge;

	//Balance Point.
	UPROPERTY()
	float MaxBP;
};
