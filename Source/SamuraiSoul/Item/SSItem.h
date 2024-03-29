// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSItem.generated.h"

class USphereComponent;

UCLASS()
class SAMURAISOUL_API ASSItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASSItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> ItemCollider;
};
