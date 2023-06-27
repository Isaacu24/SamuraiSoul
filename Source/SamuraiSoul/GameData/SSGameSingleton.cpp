// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/SSGameSingleton.h"

DEFINE_LOG_CATEGORY(LogSSGameSingleton);

USSGameSingleton::USSGameSingleton()
{
}

USSGameSingleton& USSGameSingleton::Get()
{
	USSGameSingleton* Singleton = CastChecked<USSGameSingleton>(GEngine->GameSingleton);

	if (nullptr != Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogSSGameSingleton, Error, TEXT("Invalid Game Singleton"));

	return *NewObject<USSGameSingleton>();
}
