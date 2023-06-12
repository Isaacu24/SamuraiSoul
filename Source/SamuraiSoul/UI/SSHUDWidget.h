// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSHUDWidget.generated.h"

class USSHPBarWidget;
class UImage;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USSHUDWidget(const FObjectInitializer& ObjectInitializer);

	void SetVisibilityBossHPBar(ESlateVisibility Value);

	void SetMaxPlayerHP(float Value);
	void UpdatePlayerHPbar(float Value);

	void OnDeathScreen();

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<USSHPBarWidget> PlayerHPBar;

	UPROPERTY()
	TObjectPtr<USSHPBarWidget> BossHPBar;

	UPROPERTY()
	TObjectPtr<UImage> DeathScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeIn;
};
