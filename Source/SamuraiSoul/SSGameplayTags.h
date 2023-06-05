// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/Map.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

struct FSSGameplayTags
{
public:
	FSSGameplayTags();

	static const FSSGameplayTags& Get() { return GameplayTags; }

public:
	//Ability
	FGameplayTag AbilityTag;
	FGameplayTag Ability_JumpTag;
	FGameplayTag Ability_DodgeTag;
	FGameplayTag Ability_EquipUnarmTag;
	FGameplayTag Ability_SlashTag;
	FGameplayTag Ability_DefenseTag;
	FGameplayTag BeExecutedTag;
	FGameplayTag Ability_ExecutionTag;

	//Hit
	FGameplayTag HitTag;
	FGameplayTag DeadTag;
	FGameplayTag ReboundTag;

	//Input
	FGameplayTag Input_MoveTag;
	FGameplayTag Input_LookTag;
	FGameplayTag Input_RunTag;
	FGameplayTag Input_UnRunTag;
	FGameplayTag Input_CrouchStartTag;
	FGameplayTag Input_CrouchEndTag;
	FGameplayTag Input_LockOnTag;
	FGameplayTag Input_ChangeControlTag;

	FGameplayTag Input_JumpTag;
	FGameplayTag Input_DodgeTag;
	FGameplayTag Input_EquipAndUnarmTag;
	FGameplayTag Input_SlashTag;
	FGameplayTag Input_DefenseTag;

protected:

private:
	static FSSGameplayTags GameplayTags;
};
