// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/SSWeapon.h"
#include "SSWeapon_Katana.generated.h"

class UPrimitiveComponent;
class AActor;
class UBoxComponent;
class USphereComponent;
class USceneComponent;
class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSWeapon_Katana : public ASSWeapon
{
	GENERATED_BODY()

public:
	ASSWeapon_Katana();

protected:
	UFUNCTION()
	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
