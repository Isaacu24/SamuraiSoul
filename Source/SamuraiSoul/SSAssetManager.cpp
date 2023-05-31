// Fill out your copyright notice in the Description page of Project Settings.

#include "SSAssetManager.h"
#include "SSGameplayTags.h"

USSAssetManager::USSAssetManager()
{
}

USSAssetManager& USSAssetManager::Get()
{
}

void USSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	InitializeAbilitySystem();
}

void USSAssetManager::InitializeAbilitySystem()
{
	//Init GameplayTags
	FSSGameplayTags::InitializeNativeTags();

}
