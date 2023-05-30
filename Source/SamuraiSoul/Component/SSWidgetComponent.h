// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SSWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	USSWidgetComponent();

	virtual void InitWidget() override;
};
