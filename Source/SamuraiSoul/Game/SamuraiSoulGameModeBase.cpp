// Copyright Epic Games, Inc. All Rights Reserved.


#include "SamuraiSoulGameModeBase.h"

#include "Character/SSEnemyBossCharacter.h"
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
		EEnemyType EnemyType = SpawnEnemyDataTable[i].EnemyType;

		switch (EnemyType)
		{
			case EEnemyType::Katana:
				GetWorld()->SpawnActor<ASSEnemyCharacter>(EnemyClass, SpawnEnemyDataTable[i].SpawnLocation,
				                                          SpawnEnemyDataTable[i].SpawnRotation);
				break;

			case EEnemyType::Boss:
				GetWorld()->SpawnActor<ASSEnemyBossCharacter>(BossClass, SpawnEnemyDataTable[i].SpawnLocation,
				                                              SpawnEnemyDataTable[i].SpawnRotation);
				break;
		}
	}
}
