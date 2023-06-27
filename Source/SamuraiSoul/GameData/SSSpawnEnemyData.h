#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SSSpawnEnemyData.generated.h"

UENUM()
enum class EEnemyType : uint8
{
	None,
	Katana,
	Boss
};

USTRUCT(BlueprintType)
struct FSSSpawnEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSSSpawnEnemyData() : SpawnLocation(), SpawnRotation(), EnemyType(EEnemyType::None)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpawnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyType EnemyType;
};
