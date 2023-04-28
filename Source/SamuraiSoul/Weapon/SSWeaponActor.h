// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSWeaponActor.generated.h"

class UPrimitiveComponent;
class AActor;
class UBoxComponent;
class USphereComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class SAMURAISOUL_API ASSWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<UBoxComponent> WeaponCollider;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ColliderStart;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ColliderEnd;

	//UPROPERTY(VisibleAnywhere, Category = Weapon)
	//TObjectPtr<USphereComponent> Sphere;
};
