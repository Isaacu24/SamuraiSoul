// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSHUDWidget.h"
#include "SSSamuraiHUDWidget.generated.h"

class UImage;
class UEditableTextBox;
class USSHPBarWidget;
class USSBalanceGaugeWidget;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSSamuraiHUDWidget : public USSHUDWidget
{
	GENERATED_BODY()

public:
	USSSamuraiHUDWidget(const FObjectInitializer& ObjectInitializer);

	void SetVisibilityBossHUD(ESlateVisibility Value) const;

	void SetMaxPlayerHP(float Value) const;
	void UpdatePlayerHPbar(float Value) const;
	void UpdatePlayerBPGauge(float Value) const;

	void OnDeathScreen();

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<USSHPBarWidget> PlayerHPBar;

	UPROPERTY()
	TObjectPtr<USSBalanceGaugeWidget> PlayerBPGauge;

	UPROPERTY()
	TObjectPtr<USSHPBarWidget> BossHPBar;

	UPROPERTY()
	TObjectPtr<UEditableTextBox> BossName;

	UPROPERTY()
	TObjectPtr<USSBalanceGaugeWidget> BossBPGauge;

	UPROPERTY()
	TObjectPtr<UImage> DeathScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeIn;
};
