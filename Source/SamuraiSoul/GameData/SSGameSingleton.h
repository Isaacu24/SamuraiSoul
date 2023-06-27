// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSSGameSingleton, Error, All);

UCLASS()
class SAMURAISOUL_API USSGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	USSGameSingleton();
	static USSGameSingleton& Get();
};
