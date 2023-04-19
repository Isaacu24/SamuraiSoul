// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInputConfigData.h"

const UInputAction* USSInputConfigData::FindNativeInputActionByTag(const FGameplayTag& NewInputTag, bool bLogNotFound) const
{
	for (const FTagBindingInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(NewInputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *NewInputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}


const UInputAction* USSInputConfigData::FindAbilityInputActionByTag(const FGameplayTag& NewInputTag, bool bLogNotFound) const
{
	for (const FTagBindingInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(NewInputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *NewInputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}