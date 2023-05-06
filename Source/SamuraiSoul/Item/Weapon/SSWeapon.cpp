// Fill out your copyright notice in the Description page of Project Settings.


#include "SSWeapon.h"
#include "Game/SamuraiSoul.h"
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Interface/SSCombatInterface.h"
#include "Component/SSCombatComponent.h"

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
		ETraceTypeQuery::TraceTypeQuery1,
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

	ISSCombatInterface* Enemy = Cast<ISSCombatInterface>(OtherActor);
	ISSCombatInterface* MyOwner = Cast<ISSCombatInterface>(GetOwner());

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


