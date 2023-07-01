// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSUserWidget.h"
#include "SSEnemyHUDWidget.generated.h"

class USSHPBarWidget;
class USSBalanceGaugeWidget;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSEnemyHUDWidget : public USSUserWidget
{
	GENERATED_BODY()

public:
	USSEnemyHUDWidget(const FObjectInitializer& ObjectInitializer);

	void SetMaxEnemyHP(float Value) const;
	void SetMaxEnemyBPGauge(float Value) const;
	void UpdateEnemyHPbar(float Value) const;
	void UpdateEnemyBPGauge(float Value) const;

	void OffEnemyBPGauge() const;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<USSHPBarWidget> EnemyHPBar;

	UPROPERTY()
	TObjectPtr<USSBalanceGaugeWidget> EnemyBPGauge;
};
