// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESSAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Jump,
	Dodge,
	EquipUnarm,
	Slash,
	Defense
};

UENUM(BlueprintType)
enum class ESSAbilityID : uint8
{
	None,
	Confirm,
	Cancel,
	Jump,
	Dodge,
	EquipUnarm,
	Slash,
	Defense,
	Execution
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Slash,
	Stab
};