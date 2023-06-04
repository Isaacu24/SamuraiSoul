// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/SSInputConfigData.h"
#include "InputTriggers.h"
#include "GameplayTagContainer.h"
#include "SSInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename FuncType>
	void BindNativeAction(const USSInputConfigData* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const USSInputConfigData* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};


template <class UserClass, typename FuncType>
void USSInputComponent::BindNativeAction(const USSInputConfigData* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object,
                                         FuncType Func)
{
	ensure(InputConfig);

	const UInputAction* InputAction = InputConfig->FindNativeInputActionByTag(InputTag);

	BindAction(InputAction, TriggerEvent, Object, Func);
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void USSInputComponent::BindAbilityActions(const USSInputConfigData* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	ensure(InputConfig);

	for (const FTagBindingInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (nullptr == Action.InputAction || false == Action.InputTag.IsValid())
		{
			continue;
		}

		if (PressedFunc != nullptr)
		{
			BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
		}

		if (ReleasedFunc != nullptr)
		{
			BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
		}
	}
}
