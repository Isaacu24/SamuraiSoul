// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController.h"

ASSPlayerController::ASSPlayerController()
{
}

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode = {};
	SetInputMode(GameOnlyInputMode);
}
