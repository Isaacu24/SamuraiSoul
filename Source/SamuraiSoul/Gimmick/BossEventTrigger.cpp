// Fill out your copyright notice in the Description page of Project Settings.

#include "BossEventTrigger.h"
#include "Components/BoxComponent.h"

ABossEventTrigger::ABossEventTrigger()
{
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABossEventTrigger::OnBoxOverlapBegin);
}

void ABossEventTrigger::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
                                          bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
