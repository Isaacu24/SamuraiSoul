// Fill out your copyright notice in the Description page of Project Settings.

#include "EventTrigger.h"
#include <Components/BoxComponent.h>

AEventTrigger::AEventTrigger()
{
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Collision"));
	Collider->SetCollisionProfileName("EventTrigger");
	Collider->SetBoxExtent(FVector{5.f, 5.f, 5.f});
	Collider->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void AEventTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEventTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventTrigger::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
                                      bool bFromSweep, const FHitResult& SweepResult)
{
}

void AEventTrigger::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
}
