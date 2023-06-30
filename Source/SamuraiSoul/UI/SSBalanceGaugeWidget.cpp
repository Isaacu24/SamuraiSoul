// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSBalanceGaugeWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/SSCharacterWidgetInterface.h"

USSBalanceGaugeWidget::USSBalanceGaugeWidget(const FObjectInitializer& ObjectInitializer)
{
}

void USSBalanceGaugeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Gauge = Cast<UProgressBar>(GetWidgetFromName(TEXT("GaugeBar")));
	ensure(Gauge);

	ISSCharacterWidgetInterface* CharacterWidget = Cast<ISSCharacterWidgetInterface>(OwningActor);

	if (nullptr != CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void USSBalanceGaugeWidget::UpdateBPGauge(float NewCurrentBP) const
{
	if (nullptr != Gauge)
	{
		Gauge->SetPercent(NewCurrentBP / MaxBP);
	}
}
