// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "SSInputConfigData.generated.h"

USTRUCT(BlueprintType)
struct FTagBindingInputAction
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly)
		const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
		FGameplayTag InputTag;
};

UCLASS()
class SAMURAISOUL_API USSInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindNativeInputActionByTag(const FGameplayTag& NewInputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& NewInputTag, bool bLogNotFound = true) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputActions"))
		TArray<FTagBindingInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputActions"))
		TArray<FTagBindingInputAction> AbilityInputActions;
};
