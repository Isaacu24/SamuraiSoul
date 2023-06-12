// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHUDWidget.h"
#include "Components/Image.h"
#include "UI/SSHPBarWidget.h"
#include "Interface/SSCharacterHUDInterface.h"

USSHUDWidget::USSHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BossHPBar = Cast<USSHPBarWidget>(GetWidgetFromName(TEXT("Boss_HPBar")));
	ensure(BossHPBar);

	PlayerHPBar = Cast<USSHPBarWidget>(GetWidgetFromName(TEXT("Player_HPBar")));
	ensure(BossHPBar);

	DeathScreen = Cast<UImage>(GetWidgetFromName(TEXT("Death_Screen")));
	ensure(DeathScreen);

	ISSCharacterHUDInterface* HUDPawn = Cast<ISSCharacterHUDInterface>(GetOwningPlayerPawn());

	if (nullptr != HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}

	SetVisibilityBossHPBar(ESlateVisibility::Hidden);
}

void USSHUDWidget::UpdatePlayerHPbar(float Value)
{
	PlayerHPBar->UpdateHPBar(Value);
}

void USSHUDWidget::OnDeathScreen()
{
	PlayAnimation(FadeIn);
}

void USSHUDWidget::SetVisibilityBossHPBar(ESlateVisibility Value)
{
	BossHPBar->SetVisibility(Value);
}

void USSHUDWidget::SetMaxPlayerHP(float Value)
{
	PlayerHPBar->SetMaxHp(Value);
}
