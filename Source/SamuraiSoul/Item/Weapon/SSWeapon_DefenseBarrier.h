// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSWeapon.h"
#include "SSWeapon_DefenseBarrier.generated.h"

UCLASS()
class SAMURAISOUL_API ASSWeapon_DefenseBarrier : public ASSWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSWeapon_DefenseBarrier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
