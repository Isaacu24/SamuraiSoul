// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHPBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/SSCharacterWidgetInterface.h"

USSHPBarWidget::USSHPBarWidget(const FObjectInitializer& ObjectInitializer)
{
}

void USSHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	ensure(HPProgressBar);

	ISSCharacterWidgetInterface* CharacterWidget = Cast<ISSCharacterWidgetInterface>(OwningActor);

	if (nullptr != CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void USSHPBarWidget::UpdateHPBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);

	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}
