// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include <Components/BoxComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Interface/SSCombatInterface.h>
#include "Component/SSCombatComponent.h"

ASSWeapon_DefenseBarrier::ASSWeapon_DefenseBarrier()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collider"));
	WeaponCollider->SetupAttachment(Mesh);
	WeaponCollider->SetRelativeLocation(FVector{ 0.f, 0.f, 20.f });
	WeaponCollider->SetRelativeRotation(FRotator{ 0.f, 90.f, 0.f });
	WeaponCollider->SetBoxExtent(FVector{ 75.f, 5.f, 100.f });

	WeaponCollider->SetCollisionProfileName("SSWeapon");
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponCollider->bHiddenInGame = false;

	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeapon_DefenseBarrier::OnBoxOverlapBegin);
}

void ASSWeapon_DefenseBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != GetOwner())
	{
		FVector BarrierPos = GetOwner()->GetActorForwardVector() * 75.f;
		FRotator BarrierRot = GetOwner()->GetActorRotation();
		SetActorLocation(GetOwner()->GetActorLocation() + BarrierPos);
		SetActorRotation(BarrierRot);
	}
}

void ASSWeapon_DefenseBarrier::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWeapon_DefenseBarrier::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector A = GetOwner()->GetActorForwardVector();
	FVector B = OtherActor->GetOwner()->GetActorForwardVector();

	float ReturnValue = FVector::DotProduct(A, B);
	UE_LOG(LogTemp, Log, TEXT("Dot Return Value: %f"), ReturnValue);

	if (0.5f <= ReturnValue)
	{
		return;
	}

	ASSWeapon* Weapon = Cast<ASSWeapon>(OtherActor);

	if (nullptr != Weapon)
	{
		ISSCombatInterface* MyOwner = Cast<ISSCombatInterface>(GetOwner());
		ISSCombatInterface* Enemy = Cast<ISSCombatInterface>(OtherActor->GetOwner());

		if (MyOwner == Enemy)
		{
			return;
		}

		if (nullptr != MyOwner
			&& nullptr != Enemy)
		{
			if (nullptr != MyOwner->GetCombatComponent()
				&& nullptr != Enemy->GetCombatComponent())	
			{
				//MyOwner->GetCombatComponent()->SetEnemy(Enemy);
				MyOwner->GetCombatComponent()->ExecutionEvent.Execute();
				Enemy->GetCombatComponent()->ExecutedEvent.Execute();
			}
		}
	}
}
