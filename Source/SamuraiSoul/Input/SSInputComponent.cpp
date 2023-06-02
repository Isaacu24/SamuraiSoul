// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/SSInputComponent.h"
#include "EnhancedInputSubsystems.h"


void USSInputComponent::SetMappingContext(const USSInputConfigData* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	ensure(InputConfig);
	ensure(InputSubsystem);
	ensure(InputConfig->InputMappingContext);

	InputSubsystem->AddMappingContext(InputConfig->InputMappingContext, 0);
}
