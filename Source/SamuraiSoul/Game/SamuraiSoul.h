// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

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
	SpinSlash,
	Stab,
	WolfDraw,
	Defense,
	Execution,
	BeExecuted,
	Assassination,
	BeAssassinated,
	Parry,
	Rebound,
	HandAndSwordSwing,
	RunningAttack,
	Swing,
	SwingAndSlam,
	UppercutAttack,
	Hit,
	Dead
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Katana,
	Bow,
	Defense,
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Normal,
	SpecialAttack
};

UENUM(BlueprintType)
enum class EDefenseState : uint8
{
	Defense,
	Parry
	//Defelect
};

UENUM(BlueprintType)
enum class ECharacterControlType : uint8
{
	Keyboard,
	Gamepad
};

UENUM()
enum class EDirection : uint8
{
	Foward,
	Back,
	Right,
	Left
};
