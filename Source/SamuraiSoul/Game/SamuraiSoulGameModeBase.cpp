// Copyright Epic Games, Inc. All Rights Reserved.


#include "SamuraiSoulGameModeBase.h"
#include "Gimmick/SpawnActor.h"

ASamuraiSoulGameModeBase::ASamuraiSoulGameModeBase()
{
	SpawnActor = CreateDefaultSubobject<ASpawnActor>(TEXT("Actor Spawner"));
}
