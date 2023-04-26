// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//통상의 구조체랑 이넘을 몰아넣자
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
	Idle,
	Move,
	Run,
	Jump,
	Crouch,
	Dodge,
	EquipUnarm,
	Slash,
	Defense
};