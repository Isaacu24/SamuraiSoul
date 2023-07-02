// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSSamuraiHUDWidget.h"
#include "SSBalanceGaugeWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "UI/SSHPBarWidget.h"
#include "Interface/SSCharacterHUDInterface.h"

USSSamuraiHUDWidget::USSSamuraiHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USSSamuraiHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerHPBar = Cast<USSHPBarWidget>(GetWidgetFromName(TEXT("Player_HPBar")));
	ensure(PlayerHPBar);

	PlayerBPGauge = Cast<USSBalanceGaugeWidget>(GetWidgetFromName(TEXT("Player_BPGauge")));
	ensure(PlayerBPGauge);
	PlayerBPGauge->SetVisibility(ESlateVisibility::Hidden);

	BossHPBar = Cast<USSHPBarWidget>(GetWidgetFromName(TEXT("Boss_HPBar")));
	ensure(BossHPBar);

	BossName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Boss_Name")));
	ensure(BossName);

	BossBPGauge = Cast<USSBalanceGaugeWidget>(GetWidgetFromName(TEXT("Boss_BPGauge")));
	ensure(BossBPGauge);

	DeathScreen = Cast<UImage>(GetWidgetFromName(TEXT("Death_Screen")));
	ensure(DeathScreen);

	ISSCharacterHUDInterface* HUDPawn = Cast<ISSCharacterHUDInterface>(GetOwningPlayerPawn());

	if (nullptr != HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}

	SetVisibilityBossHUD(ESlateVisibility::Hidden);
}

void USSSamuraiHUDWidget::UpdatePlayerHPbar(float Value) const
{
	PlayerHPBar->UpdateHPBar(Value);
}

void USSSamuraiHUDWidget::UpdatePlayerBPGauge(float Value) const
{
	if (ESlateVisibility::Hidden == PlayerBPGauge->GetVisibility())
	{
		PlayerBPGauge->SetVisibility(ESlateVisibility::Visible);
	}

	PlayerBPGauge->UpdateBPGauge(Value);
}

void USSSamuraiHUDWidget::SetBossMaxHP(float Value) const
{
	BossHPBar->SetMaxHP(Value);
}

void USSSamuraiHUDWidget::SetBossMaxBP(float Value) const
{
	BossBPGauge->SetMaxBP(Value);
}

void USSSamuraiHUDWidget::UpdateBossHPbar(float Value) const
{
	BossHPBar->UpdateHPBar(Value);
}

void USSSamuraiHUDWidget::UpdateBossBPGauge(float Value) const
{
	BossBPGauge->UpdateBPGauge(Value);
}

void USSSamuraiHUDWidget::SetBossName(const FString& Name) const
{
	BossName->SetText(FText::FromString(Name));
}

void USSSamuraiHUDWidget::OnDeathScreen()
{
	PlayAnimation(FadeIn);
}

void USSSamuraiHUDWidget::OffPlayerBPGauge() const
{
	PlayerBPGauge->SetVisibility(ESlateVisibility::Hidden);
}

void USSSamuraiHUDWidget::SetVisibilityBossHUD(ESlateVisibility Value) const
{
	BossHPBar->SetVisibility(Value);
	BossName->SetVisibility(Value);
	BossBPGauge->SetVisibility(Value);
}

void USSSamuraiHUDWidget::SetHiddenBossHUD() const
{
	SetVisibilityBossHUD(ESlateVisibility::Hidden);
}

void USSSamuraiHUDWidget::SetPlayerMaxHP(float Value) const
{
	PlayerHPBar->SetMaxHP(Value);
}

void USSSamuraiHUDWidget::SetPlayerMaxBP(float Value) const
{
	PlayerBPGauge->SetMaxBP(Value);
}
