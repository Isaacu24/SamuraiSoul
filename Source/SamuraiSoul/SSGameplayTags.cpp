// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameplayTags.h"

FSSGameplayTags FSSGameplayTags::GameplayTags;

FSSGameplayTags::FSSGameplayTags()
{
	AbilityTag                   = FGameplayTag::RequestGameplayTag(FName("SSAbilities"));
	Ability_JumpTag              = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Jump"));
	Ability_DodgeTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Dodge"));
	Ability_EquipUnarmTag        = FGameplayTag::RequestGameplayTag(FName("SSAbilities.EquipUnarm"));
	Ability_SlashTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Slash"));
	Ability_SpinSlashTag         = FGameplayTag::RequestGameplayTag(FName("SSAbilities.SpinSlash"));
	Ability_StabTag              = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Stab"));
	Ability_WolfDrawTag          = FGameplayTag::RequestGameplayTag(FName("SSAbilities.WolfDraw"));
	Ability_DefenseTag           = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Defense"));
	Ability_ParryTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Parry"));
	Ability_AssassinationTag     = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Assassination"));
	Ability_UppercutAttackTag    = FGameplayTag::RequestGameplayTag(FName("SSAbilities.UppercutAttack"));
	Ability_SwingAndSlamTag      = FGameplayTag::RequestGameplayTag(FName("SSAbilities.SwingAndSlam"));
	Ability_SwingTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Swing"));
	Ability_RunningAttackTag     = FGameplayTag::RequestGameplayTag(FName("SSAbilities.RunningAttack"));
	Ability_HandAndSwordSwingTag = FGameplayTag::RequestGameplayTag(FName("SSAbilities.HandAndSwordSwing"));

	DeferredAbilityTag           = FGameplayTag::RequestGameplayTag(FName("SSDeferredAbilities"));
	DeferredAbility_ExecutionTag = FGameplayTag::RequestGameplayTag(FName("SSDeferredAbilities.Execution"));

	ReactionTag       = FGameplayTag::RequestGameplayTag(FName("Reaction"));
	HitTag            = FGameplayTag::RequestGameplayTag(FName("Reaction.Hit"));
	DeadTag           = FGameplayTag::RequestGameplayTag(FName("Reaction.Dead"));
	ReboundTag        = FGameplayTag::RequestGameplayTag(FName("Reaction.Rebound"));
	BeExecutedTag     = FGameplayTag::RequestGameplayTag(FName("Reaction.BeExecuted"));
	BeAssassinatedTag = FGameplayTag::RequestGameplayTag(FName("Reaction.BeAssassinated"));

	Input_MoveTag          = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Move"));
	Input_LookTag          = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Look"));
	Input_RunTag           = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Run"));
	Input_UnRunTag         = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.UnRun"));
	Input_CrouchTag        = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Crouch"));
	Input_LockOnTag        = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.LockOn"));
	Input_ChangeControlTag = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.ChangeControl"));

	Input_JumpTag       = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Jump"));
	Input_DodgeTag      = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Dodge"));
	Input_EquipUnarmTag = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.EquipUnarm"));
	Input_SlashTag      = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Attack"));
	Input_DefenseTag    = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Defense"));
}
