// Fill out your copyright notice in the Description page of Project Settings.

#include "SSAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "SSGameplayTags.h"
#include "Engine/Engine.h"

USSAssetManager::USSAssetManager()
{
}

USSAssetManager& USSAssetManager::Get()
{
	check(GEngine);

	if (USSAssetManager* Singleton = Cast<USSAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	// Fatal error above prevents this from being called.
	return *NewObject<USSAssetManager>();
}

void USSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();

	FSSGameplayTags::InitGameplayTag();
}
