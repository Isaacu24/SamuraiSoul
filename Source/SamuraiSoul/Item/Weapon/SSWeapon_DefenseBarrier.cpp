// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include <Components/BoxComponent.h>

// Sets default values
ASSWeapon_DefenseBarrier::ASSWeapon_DefenseBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collider"));
	WeaponCollider->SetupAttachment(Mesh);
	WeaponCollider->SetRelativeLocation(FVector{ 0.f, 0.f, 20.f });
	WeaponCollider->SetRelativeRotation(FRotator{ 0.f, 90.f, 0.f });
	WeaponCollider->SetBoxExtent(FVector{ 75.f, 5.f, 100.f });
	WeaponCollider->bHiddenInGame = false;

	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeapon_DefenseBarrier::OnBoxOverlapBegin);
}

void ASSWeapon_DefenseBarrier::OnParry()
{
	//WeaponCollider->SetCollisionProfileName("Parry");
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASSWeapon_DefenseBarrier::OffDefense()
{
	WeaponCollider->SetCollisionProfileName("NoCollision");
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASSWeapon_DefenseBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASSWeapon_DefenseBarrier::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

// Called every frame
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

