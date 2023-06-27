// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSBalanceWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/SSCharacterWidgetInterface.h"

USSBalanceWidget::USSBalanceWidget(const FObjectInitializer& ObjectInitializer)
{
}

void USSBalanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Gauge = Cast<UProgressBar>(GetWidgetFromName(TEXT("Gauge")));
	ensure(Gauge);

	ISSCharacterWidgetInterface* CharacterWidget = Cast<ISSCharacterWidgetInterface>(OwningActor);

	if (nullptr != CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void USSBalanceWidget::UpdateHPBar(float NewCurrentHp) const
{
	ensure(MaxBP > 0.0f);

	if (nullptr != Gauge)
	{
		Gauge->SetPercent(NewCurrentHp / MaxBP);
	}
}
