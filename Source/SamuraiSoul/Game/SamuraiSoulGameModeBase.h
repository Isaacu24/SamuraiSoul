// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameData/SSSpawnEnemyData.h"
#include "GameFramework/GameModeBase.h"
#include "SamuraiSoulGameModeBase.generated.h"

class ASSEnemyBossCharacter;
class ASSEnemyCharacter;
class USSAICharacterStatData;

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

	ASSEnemyBossCharacter* GetBossEnemyCharacter(const FName& Key) const;

protected:

private:
	const UDataTable* SpawnEnemyDataTable;
	TArray<FSSSpawnEnemyData> SpawnEnemyDataArray;

	TMap<FString, ASSEnemyBossCharacter*> SpawnBossMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ASSEnemyCharacter>> EnemyClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASSEnemyBossCharacter> BossClass;
};
