// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHPBarWidget.h"
#include "Components/ProgressBar.h"

USSHPBarWidget::USSHPBarWidget(const FObjectInitializer& ObjectInitializer)
{
}

void USSHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar")));
	ensure(HpProgressBar);
}

void USSHPBarWidget::UpdateHpBar(float NewCurrentHp)
{
}
