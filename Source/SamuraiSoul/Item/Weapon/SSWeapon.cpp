// Fill out your copyright notice in the Description page of Project Settings.


#include "SSWeapon.h"
#include "Game/SamuraiSoul.h"
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Interface/SSCombatInterface.h"
#include "Component/SSCombatComponent.h"
#include <Engine/StaticMeshActor.h>

ASSWeapon::ASSWeapon()
{

}

void ASSWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWeapon::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = ColliderStart->GetComponentLocation();
	const FVector End = ColliderEnd->GetComponentLocation();

	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore = {}; 
	ActorsToIgnore.Add(this);
	if (nullptr != GetOwner())
	{
		ActorsToIgnore.Add(GetOwner());
	}

	UKismetSystemLibrary::BoxTraceSingle(
		this, 
		Start, 
		End, 
		FVector(5.f, 5.f, 5.f), 
		ColliderStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f
	);

	if (nullptr != OutHit.GetActor())
	{
		DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 25.f, 12, FColor::Green, false, 1.f);
	}

	ISSCombatInterface* MyOwner = Cast<ISSCombatInterface>(GetOwner());
	ISSCombatInterface* Enemy = nullptr;

	if (OtherActor != GetOwner())
	{
		Enemy = Cast<ISSCombatInterface>(OtherActor);
	}

	if (nullptr != Enemy)
	{
		Enemy->GetCombatComponent()->HitEvent.Execute();
	}


	if (nullptr == MyOwner)
	{
		//MyOwner->GetCombatComponent()->AttackEvent.Execute();
	}
}

void ASSWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	if (nullptr != InParent)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(InParent, TransformRules, InSocketName);
	}
}

void ASSWeapon::SetEnemyWeapon()
{
	WeaponCollider->SetCollisionProfileName("EnemyWeapon");
}


