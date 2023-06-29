// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameData/SSSpawnEnemyData.h"
#include "GameFramework/GameModeBase.h"
#include "SamuraiSoulGameModeBase.generated.h"

class ASSEnemyBossCharacter;
class ASSEnemyCharacter;

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

	void SpawnEnemy();
	ASSEnemyBossCharacter* SetBossDataInHUD(const FName& Key);

protected:

private:
	const UDataTable* SpawnEnemyDataTable;
	TArray<FSSSpawnEnemyData> SpawnEnemyDataArray;

	TMap<FString, ASSEnemyBossCharacter*> SpawnBossMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASSEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASSEnemyBossCharacter> BossClass;
};
