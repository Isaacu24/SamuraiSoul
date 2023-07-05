// Fill out your copyright notice in the Description page of Project Settings.

#include "BossEventTrigger.h"

#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Character/SSEnemyBossCharacter.h"
#include "Game/SamuraiSoulGameModeBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ABossEventTrigger::ABossEventTrigger()
{
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABossEventTrigger::OnBoxOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ABossEventTrigger::OnBoxOverlapEnd);

	LevelSequence      = CreateDefaultSubobject<ULevelSequence>(TEXT("LevelSequence"));
	LevelSequenceActor = CreateDefaultSubobject<ALevelSequenceActor>(TEXT("LevelSequenceActor"));
}

void ABossEventTrigger::BeginPlay()
{
	Super::BeginPlay();


	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bAutoPlay   = false;
	Settings.bPauseAtEnd = true;
	LevelSequencePlayer  = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Settings, LevelSequenceActor);
}

void ABossEventTrigger::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
                                          bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ACharacter* Player = Cast<ACharacter>(OtherActor);

	if (nullptr == Player)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());

	if (nullptr == PlayerController)
	{
		return;
	}

	ASamuraiSoulGameModeBase* GameMode = Cast<ASamuraiSoulGameModeBase>(GetWorld()->GetAuthGameMode());

	if (nullptr != GameMode)
	{
		ASSEnemyBossCharacter* Boss = GameMode->SetBossDataInHUD(KeyName);
		Boss->RunAI();
		Boss->BattleEntrance();
		Boss->OnCharacterDead.AddUObject(this, &ABossEventTrigger::DestroyTrigger);
	}

	if (nullptr != LevelSequencePlayer)
	{
		LevelSequencePlayer->Play();
	}
}

void ABossEventTrigger::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);

	if (nullptr == Player)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());

	if (nullptr == PlayerController)
	{
		return;
	}

	Collider->SetCollisionProfileName(FName("BlockAllDynamic"));
}

void ABossEventTrigger::DestroyTrigger()
{
	Destroy();
}
