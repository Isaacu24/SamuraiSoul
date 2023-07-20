// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameplayTags.h"

FSSGameplayTags FSSGameplayTags::GameplayTags;

FSSGameplayTags::FSSGameplayTags()
{
}

void FSSGameplayTags::InitGameplayTag()
{
	GameplayTags.AbilityTag                   = FGameplayTag::RequestGameplayTag(FName("SSAbilities"));
	GameplayTags.Ability_JumpTag              = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Jump"));
	GameplayTags.Ability_DodgeTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Dodge"));
	GameplayTags.Ability_EquipUnarmTag        = FGameplayTag::RequestGameplayTag(FName("SSAbilities.EquipUnarm"));
	GameplayTags.Ability_SlashTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Slash"));
	GameplayTags.Ability_SpinSlashTag         = FGameplayTag::RequestGameplayTag(FName("SSAbilities.SpinSlash"));
	GameplayTags.Ability_StabTag              = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Stab"));
	GameplayTags.Ability_WolfDrawTag          = FGameplayTag::RequestGameplayTag(FName("SSAbilities.WolfDraw"));
	GameplayTags.Ability_DefenseTag           = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Defense"));
	GameplayTags.Ability_ParryTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Parry"));
	GameplayTags.Ability_AssassinationTag     = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Assassination"));
	GameplayTags.Ability_UppercutAttackTag    = FGameplayTag::RequestGameplayTag(FName("SSAbilities.UppercutAttack"));
	GameplayTags.Ability_SwingAndSlamTag      = FGameplayTag::RequestGameplayTag(FName("SSAbilities.SwingAndSlam"));
	GameplayTags.Ability_SwingTag             = FGameplayTag::RequestGameplayTag(FName("SSAbilities.Swing"));
	GameplayTags.Ability_RunningAttackTag     = FGameplayTag::RequestGameplayTag(FName("SSAbilities.RunningAttack"));
	GameplayTags.Ability_HandAndSwordSwingTag = FGameplayTag::RequestGameplayTag(FName("SSAbilities.HandAndSwordSwing"));

	GameplayTags.DeferredAbilityTag           = FGameplayTag::RequestGameplayTag(FName("SSDeferredAbilities"));
	GameplayTags.DeferredAbility_ExecutionTag = FGameplayTag::RequestGameplayTag(FName("SSDeferredAbilities.Execution"));

	GameplayTags.ReactionTag       = FGameplayTag::RequestGameplayTag(FName("Reaction"));
	GameplayTags.HitTag            = FGameplayTag::RequestGameplayTag(FName("Reaction.Hit"));
	GameplayTags.DeadTag           = FGameplayTag::RequestGameplayTag(FName("Reaction.Dead"));
	GameplayTags.ReboundTag        = FGameplayTag::RequestGameplayTag(FName("Reaction.Rebound"));
	GameplayTags.BeExecutedTag     = FGameplayTag::RequestGameplayTag(FName("Reaction.BeExecuted"));
	GameplayTags.BeAssassinatedTag = FGameplayTag::RequestGameplayTag(FName("Reaction.BeAssassinated"));

	GameplayTags.Input_MoveTag          = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Move"));
	GameplayTags.Input_LookTag          = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Look"));
	GameplayTags.Input_RunTag           = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Run"));
	GameplayTags.Input_UnRunTag         = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.UnRun"));
	GameplayTags.Input_CrouchTag        = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Crouch"));
	GameplayTags.Input_LockOnTag        = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.LockOn"));
	GameplayTags.Input_ChangeControlTag = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.ChangeControl"));

	GameplayTags.Input_JumpTag       = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Jump"));
	GameplayTags.Input_DodgeTag      = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Dodge"));
	GameplayTags.Input_EquipUnarmTag = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.EquipUnarm"));
	GameplayTags.Input_SlashTag      = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Attack"));
	GameplayTags.Input_DefenseTag    = FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Defense"));
}
