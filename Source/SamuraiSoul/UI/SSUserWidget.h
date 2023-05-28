// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwningActor(AActor* InActor)
	{
		OwningActor = InActor;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> OwningActor;
};
