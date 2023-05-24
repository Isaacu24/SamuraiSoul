// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController.h"
#include "UI/SSHUDWidget.h"

ASSPlayerController::ASSPlayerController()
{
	static ConstructorHelpers::FClassFinder<USSHUDWidget> HUD_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/WBP_SSHUD.WBP_SSHUD_C'"));

	if (nullptr != HUD_WIDGET.Class)
	{
		HUDWidgetClass = HUD_WIDGET.Class;
	}
}

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode = {};
	SetInputMode(GameOnlyInputMode);

	HUDWidget = CreateWidget<USSHUDWidget>(this, HUDWidgetClass);

	if (nullptr != HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
