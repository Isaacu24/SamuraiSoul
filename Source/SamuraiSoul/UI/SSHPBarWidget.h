// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSUserWidget.h"
#include "SSHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSHPBarWidget : public USSUserWidget
{
	GENERATED_BODY()

public:
	USSHPBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp)
	{
		MaxHp = NewMaxHp;
	}

	void UpdateHPBar(float NewCurrentHp) const;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	float MaxHp;
};
