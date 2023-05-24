// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHUDWidget.h"
#include "UI/SSHPBarWidget.h"

USSHUDWidget::USSHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BossHPBar = Cast<USSHPBarWidget>(GetWidgetFromName(TEXT("Boss_HPBar")));
	ensure(BossHPBar);

	SetVisibilityBossHPBar(ESlateVisibility::Hidden);
}

void USSHUDWidget::SetVisibilityBossHPBar(ESlateVisibility Value)
{
	BossHPBar->SetVisibility(Value);
}
