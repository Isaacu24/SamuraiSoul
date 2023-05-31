// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SamuraiSoulGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USamuraiSoulGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

public:
	USamuraiSoulGameInstance();
};
