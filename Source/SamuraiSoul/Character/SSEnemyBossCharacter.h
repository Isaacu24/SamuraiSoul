// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSEnemyCharacterBase.h"
#include "SSEnemyBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyBossCharacter : public ASSEnemyCharacterBase
{
	GENERATED_BODY()

public:
	ASSEnemyBossCharacter();

	virtual void Tick(float DeltaTime) override;

	void SetName(const FString& InName)
	{
		Name = InName;
	}

	const FString& GetBossName() const
	{
		return Name;
	}

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY()
	FString Name;
};
