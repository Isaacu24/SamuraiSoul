// Fill out your copyright notice in the Description page of Project Settings.


#include "SSWeapon.h"
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>

ASSWeapon::ASSWeapon()
{
}

void ASSWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWeapon::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
}

void ASSWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	if (nullptr != InParent)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(InParent, TransformRules, InSocketName);
	}
}

void ASSWeapon::SetEnemyWeapon() const
{
	WeaponCollider->SetCollisionProfileName("EnemyWeapon");
}

void ASSWeapon::CollisionHiddenInGame(bool Value) const
{
	Value ? WeaponCollider->bHiddenInGame = false : WeaponCollider->bHiddenInGame = true;
}
