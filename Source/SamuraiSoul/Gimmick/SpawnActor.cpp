// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/SpawnActor.h"
#include "Character/SSEnemyCharacter.h"

// Sets default values
ASpawnActor::ASpawnActor()
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

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < SpawnEnemyDataTable.Num(); ++i)
	{
		ASSEnemyCharacter* Enemy = GetWorld()->SpawnActor<ASSEnemyCharacter>(CharacterClass, SpawnEnemyDataTable[i].SpawnLocation,
		                                                                     SpawnEnemyDataTable[i].SpawnRotation);
	}
}
