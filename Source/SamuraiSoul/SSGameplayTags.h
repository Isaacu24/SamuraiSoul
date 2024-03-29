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

	static void InitGameplayTag();

public:
	//Ability
	FGameplayTag AbilityTag;
	FGameplayTag Ability_JumpTag;
	FGameplayTag Ability_DodgeTag;
	FGameplayTag Ability_EquipUnarmTag;
	FGameplayTag Ability_SlashTag;
	FGameplayTag Ability_SpinSlashTag;
	FGameplayTag Ability_StabTag;
	FGameplayTag Ability_WolfDrawTag;
	FGameplayTag Ability_DefenseTag;
	FGameplayTag Ability_ParryTag;
	FGameplayTag Ability_AssassinationTag;
	FGameplayTag Ability_UppercutAttackTag;
	FGameplayTag Ability_SwingAndSlamTag;
	FGameplayTag Ability_SwingTag;
	FGameplayTag Ability_RunningAttackTag;
	FGameplayTag Ability_HandAndSwordSwingTag;

	//DeferredAbility
	FGameplayTag DeferredAbilityTag;
	FGameplayTag DeferredAbility_ExecutionTag;

	//Reaction
	FGameplayTag ReactionTag;
	FGameplayTag HitTag;
	FGameplayTag DeadTag;
	FGameplayTag ReboundTag;
	FGameplayTag BeExecutedTag;
	FGameplayTag BeAssassinatedTag;

	//Input
	FGameplayTag Input_MoveTag;
	FGameplayTag Input_LookTag;
	FGameplayTag Input_RunTag;
	FGameplayTag Input_UnRunTag;
	FGameplayTag Input_CrouchTag;
	FGameplayTag Input_CrouchStartTag;
	FGameplayTag Input_CrouchEndTag;
	FGameplayTag Input_LockOnTag;
	FGameplayTag Input_ChangeControlTag;

	FGameplayTag Input_JumpTag;
	FGameplayTag Input_DodgeTag;
	FGameplayTag Input_EquipUnarmTag;
	FGameplayTag Input_SlashTag;
	FGameplayTag Input_DefenseTag;

protected:

private:
	static FSSGameplayTags GameplayTags;
};
