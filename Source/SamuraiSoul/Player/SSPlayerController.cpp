// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SSAbilitySystemComponent.h"
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

void ASSPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetPawn());

	check(AbilityPawn);
	check(AbilityPawn->GetAbilitySystemComponent());

	USSAbilitySystemComponent* ASC = Cast<USSAbilitySystemComponent>(AbilityPawn->GetAbilitySystemComponent());
	ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
}
