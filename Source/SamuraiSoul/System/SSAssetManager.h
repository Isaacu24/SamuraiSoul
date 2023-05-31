// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "SSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	USSAssetManager();

	// Returns the AssetManager singleton object.
	static USSAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
