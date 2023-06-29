// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/EventTrigger.h"
#include "BossEventTrigger.generated.h"

class ASSEnemyBossCharacter;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ABossEventTrigger : public AEventTrigger
{
	GENERATED_BODY()

public:
	ABossEventTrigger();

protected:
	virtual void BeginPlay() override;

	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
	                               bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex) override;

	void DestroyTrigger();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FName KeyName;
};
