// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USSHUDWidget(const FObjectInitializer& ObjectInitializer);

	void SetVisibilityBossHPBar(ESlateVisibility Value);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class USSHPBarWidget> BossHPBar;
};
