// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSEnemyHUDWidget.h"
#include "SSBalanceGaugeWidget.h"
#include "SSHPBarWidget.h"
#include "Interface/SSCharacterWidgetInterface.h"


USSEnemyHUDWidget::USSEnemyHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USSEnemyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EnemyHPBar = Cast<USSHPBarWidget>(GetWidgetFromName(TEXT("Enemy_HPBar")));
	ensure(EnemyHPBar);

	EnemyBPGauge = Cast<USSBalanceGaugeWidget>(GetWidgetFromName(TEXT("Enemy_BPGauge")));
	ensure(EnemyBPGauge);
	EnemyBPGauge->SetVisibility(ESlateVisibility::Hidden);

	ISSCharacterWidgetInterface* CharacterWidget = Cast<ISSCharacterWidgetInterface>(OwningActor);

	if (nullptr != CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void USSEnemyHUDWidget::SetMaxEnemyHP(float Value) const
{
	EnemyHPBar->SetMaxHP(Value);
}

void USSEnemyHUDWidget::SetMaxEnemyBPGauge(float Value) const
{
	EnemyBPGauge->SetMaxBP(Value);
}

void USSEnemyHUDWidget::UpdateEnemyHPbar(float Value) const
{
	EnemyHPBar->UpdateHPBar(Value);
}


void USSEnemyHUDWidget::OffEnemyBPGauge() const
{
	EnemyBPGauge->SetVisibility(ESlateVisibility::Hidden);
}

void USSEnemyHUDWidget::UpdateEnemyBPGauge(float Value) const
{
	if (ESlateVisibility::Hidden == EnemyBPGauge->GetVisibility())
	{
		EnemyBPGauge->SetVisibility(ESlateVisibility::Visible);
	}

	EnemyBPGauge->UpdateBPGauge(Value);
}
