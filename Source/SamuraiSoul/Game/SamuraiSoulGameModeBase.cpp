// Copyright Epic Games, Inc. All Rights Reserved.


#include "SamuraiSoulGameModeBase.h"
#include "Character/SSEnemyCharacter.h"

ASamuraiSoulGameModeBase::ASamuraiSoulGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		DataTableRef(TEXT("/Script/Engine.DataTable'/Game/MyContent/GameData/DT_SSSpawnEnemyData.DT_SSSpawnEnemyData'"));

	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray = {};

		DataTable->GetRowMap().GenerateValueArray(ValueArray);

		Algo::Transform(ValueArray, SpawnEnemyDataTable,
		                [](uint8* Value)
		                {
			                return *reinterpret_cast<FSSSpawnEnemyData*>(Value);
		                }
		               );
	}
}

void ASamuraiSoulGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < SpawnEnemyDataTable.Num(); ++i)
	{
		ASSEnemyCharacter* Enemy = GetWorld()->SpawnActor<ASSEnemyCharacter>(CharacterClass, SpawnEnemyDataTable[i].SpawnLocation,
		                                                                     SpawnEnemyDataTable[i].SpawnRotation);
	}
}
