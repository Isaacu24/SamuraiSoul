// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSWeapon.h"
#include "SSWeapon_DefenseBarrier.generated.h"

DECLARE_DELEGATE(FDefenseHitDelegate)

UCLASS()
class SAMURAISOUL_API ASSWeapon_DefenseBarrier : public ASSWeapon
{
	GENERATED_BODY()

public:
	ASSWeapon_DefenseBarrier();

	void ChangeDefenseState(EDefenseState Type);
	bool CheckAttackDirection(FVector A, FVector B);

	FDefenseHitDelegate OnHitEvent;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
	                               const FHitResult& SweepResult) override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	EDefenseState DefenseType;
};
