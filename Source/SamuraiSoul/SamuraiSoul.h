// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESSAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Idle,
	Move,
	Run,
	Jump,
	Crouch,
	Dodge,
	EquipAndUnarm,
	Slash
};

UENUM(BlueprintType)
enum class ESSAbilityID : uint8
{
	None,
	Confirm,
	Cancel,
	Idle,
	Move,
	Run,
	Jump,
	Crouch,
	Dodge,
	EquipAndUnarm,
	Slash
};