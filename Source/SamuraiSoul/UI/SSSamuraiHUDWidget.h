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
	void SetHiddenBossHUD() const;

	void SetPlayerMaxHP(float Value) const;
	void SetPlayerMaxBP(float Value) const;
	void UpdatePlayerHPbar(float Value) const;
	void UpdatePlayerBPGauge(float Value) const;

	void SetBossMaxHP(float Value) const;
	void SetBossMaxBP(float Value) const;
	void UpdateBossHPbar(float Value) const;
	void UpdateBossBPGauge(float Value) const;

	void SetBossName(const FString& Name) const;

	void OnDeathScreen();

	void OffPlayerBPGauge() const;

	UFUNCTION()
	void OnRestart();

	FORCEINLINE bool GetIsRestart() const
	{
		return IsRestart;
	}

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 IsRestart : 1;
};
