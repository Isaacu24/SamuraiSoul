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
	FGameplayTag HitTag;
	FGameplayTag DeadTag;

protected:

private:
	static FSSGameplayTags GameplayTags;
};
