// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameplayTags.h"

FSSGameplayTags FSSGameplayTags::GameplayTags;

FSSGameplayTags::FSSGameplayTags()
{
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	HitTag  = FGameplayTag::RequestGameplayTag(FName("State.Hit"));
}
