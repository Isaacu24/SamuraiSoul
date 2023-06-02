// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASSPlayerController();

protected:
	virtual void BeginPlay();

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class USSHUDWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class USSHUDWidget> HUDWidget;
};
