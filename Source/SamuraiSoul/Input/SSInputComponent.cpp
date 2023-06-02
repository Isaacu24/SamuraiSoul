// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInputComponent.h"

#include "Containers/Map.h"
#include "InputCoreTypes.h"
#include "UObject/NameTypes.h"
#include "UObject/UnrealNames.h"

USSInputComponent::USSInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void USSInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
