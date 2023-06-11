// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SSItem.h"
#include "Game/SamuraiSoul.h"
#include "SSWeapon.generated.h"

class UBoxComponent;
class USceneComponent;
class USphereComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;

DECLARE_DELEGATE_TwoParams(FWeaponCollisionOverlap, AActor* /*InActor*/, const FHitResult& /*OutHit*/);

UCLASS()
class SAMURAISOUL_API ASSWeapon : public ASSItem
{
	GENERATED_BODY()

public:
	ASSWeapon();

	FWeaponCollisionOverlap OnWeaponOverlap;

	void Equip(USceneComponent* InParent, FName InSocketName);
	void SetEnemyWeapon();
	void CollisionHiddenInGame(bool Value);

	FORCEINLINE EWeaponType GetWeaponType() const
	{
		return WeaponType;
	}

protected:
	virtual void BeginPlay() override;

	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
	                               const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<UBoxComponent> WeaponCollider;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ColliderStart;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ColliderEnd;

	EWeaponType WeaponType;
};
