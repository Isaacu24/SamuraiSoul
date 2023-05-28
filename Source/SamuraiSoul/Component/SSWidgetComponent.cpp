// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/SSWidgetComponent.h"
#include "UI/SSUserWidget.h"

USSWidgetComponent::USSWidgetComponent()
{
}

void USSWidgetComponent::InitWidget()
{
	Super::InitWidget();

	USSUserWidget* SSUserWidget = Cast<USSUserWidget>(GetWidget());

	if (nullptr != SSUserWidget)
	{
		SSUserWidget->SetOwningActor(GetOwner());
	}
}
