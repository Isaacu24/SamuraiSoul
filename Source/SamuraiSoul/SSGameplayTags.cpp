// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameplayTags.h"

FSSGameplayTags FSSGameplayTags::GameplayTags;

FSSGameplayTags::FSSGameplayTags()
{
	AbilityTag = FGameplayTag::RequestGameplayTag(TEXT("SSAbilities"));

	HitTag  = FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Hit"));
	DeadTag = FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Dead"));
}
