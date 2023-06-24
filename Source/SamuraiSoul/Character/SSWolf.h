// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSWolf.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class USkeletalMeshComponent;
class UCapsuleComponent;
class UParticleSystem;
class ASSWolf;


DECLARE_DELEGATE_TwoParams(FWolfCollisionOverlap, AActor* /*InActor*/, const FHitResult& /*OutHit*/);

UCLASS()
class SAMURAISOUL_API ASSWolf : public AActor
{
	GENERATED_BODY()

public:
	ASSWolf();

	void RunWolf(AActor* InActor);

	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                           const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> SpawnedFX;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> SpawnedFXComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> RunMontage;

	float GravityScale;

	FWolfCollisionOverlap OnWolfOverlap;
};
