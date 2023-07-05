// Copyright Epic Games, Inc. All Rights Reserved.


#include "SamuraiSoulGameModeBase.h"
#include "Character/SSEnemyBossCharacter.h"
#include "Character/SSEnemyCharacter.h"
#include "Interface/SSCharacterHUDInterface.h"
#include "Kismet/GameplayStatics.h"

ASamuraiSoulGameModeBase::ASamuraiSoulGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		DataTableRef(TEXT("/Script/Engine.DataTable'/Game/MyContent/GameData/DT_SSSpawnEnemyData.DT_SSSpawnEnemyData'"));

	if (nullptr != DataTableRef.Object)
	{
		SpawnEnemyDataTable = DataTableRef.Object;
		check(SpawnEnemyDataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray = {};
		SpawnEnemyDataTable->GetRowMap().GenerateValueArray(ValueArray);

		Algo::Transform(ValueArray, SpawnEnemyDataArray,
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

	SpawnEnemy();
}

void ASamuraiSoulGameModeBase::SpawnEnemy()
{
	for (size_t i = 0; i < SpawnEnemyDataArray.Num(); ++i)
	{
		EEnemyType EnemyType = SpawnEnemyDataArray[i].EnemyType;

		switch (EnemyType)
		{
			case EEnemyType::Katana:
				{
					ASSEnemyCharacter* Enemy = GetWorld()->SpawnActor<ASSEnemyCharacter>(EnemyClass, SpawnEnemyDataArray[i].SpawnLocation,
					                                                                     SpawnEnemyDataArray[i].SpawnRotation);
				}
				break;

			case EEnemyType::Boss:
				{
					ASSEnemyBossCharacter* Boss = GetWorld()->SpawnActor<ASSEnemyBossCharacter>(BossClass, SpawnEnemyDataArray[i].SpawnLocation,
					                                                                            SpawnEnemyDataArray[i].SpawnRotation);
					Boss->SetName(SpawnEnemyDataArray[i].EnemyName);
					Boss->StopAI(); //Trace Player Blocking

					SpawnBossMap.Add(SpawnEnemyDataArray[i].EnemyName, Boss);
				}
				break;
		}
	}
}

ASSEnemyBossCharacter* ASamuraiSoulGameModeBase::SetBossDataInHUD(const FName& Key)
{
	FSSSpawnEnemyData* BossData = SpawnEnemyDataTable->FindRow<FSSSpawnEnemyData>(Key, "");

	ASSEnemyBossCharacter* Boss = *(SpawnBossMap.Find(BossData->EnemyName));

	if (nullptr == BossData)
	{
		return nullptr;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ISSCharacterHUDInterface* HUDPawn   = Cast<ISSCharacterHUDInterface>(PlayerController->GetPawn());

	if (nullptr == HUDPawn)
	{
		return nullptr;
	}

	HUDPawn->SetBossDataInHUD(Boss);

	return Boss;
}
