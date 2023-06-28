// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameData/SSSpawnEnemyData.h"
#include "GameFramework/GameModeBase.h"
#include "SamuraiSoulGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASamuraiSoulGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASamuraiSoulGameModeBase();

	void BeginPlay() override;

protected:

private:
	TArray<FSSSpawnEnemyData> SpawnEnemyDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASSEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASSEnemyBossCharacter> BossClass;
};
