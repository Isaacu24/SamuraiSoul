// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/SSWeapon_Katana.h"
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "Character/SSSamuraiCharacter.h"
#include "Character/SSCharacterBase.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Character/SSEnemyCharacter.h"
#include "Component/SSCombatComponent.h"

ASSWeapon_Katana::ASSWeapon_Katana()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_WEAPON(TEXT("/Script/Engine.StaticMesh'/Game/GhostSamurai_Bundle/GhostSamurai/Weapon/Mesh/Katana/SM_Katana01.SM_Katana01'"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	
	if (true == SK_WEAPON.Succeeded())
	{
		Mesh->SetStaticMesh(SK_WEAPON.Object);
	}

	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetVisibility(false);

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collider"));
	WeaponCollider->SetupAttachment(Mesh);
	WeaponCollider->SetCollisionProfileName("PlayerWeapon");
	WeaponCollider->SetRelativeLocation(FVector{ 0.f, 53.5f, 0.f });
	WeaponCollider->SetBoxExtent(FVector{ 4.f, 45.f, 4.f });
	WeaponCollider->bHiddenInGame = false;

	ColliderStart = CreateDefaultSubobject<USceneComponent>(TEXT("Collider Start"));
	ColliderStart->SetupAttachment(Mesh);
	ColliderStart->SetRelativeLocation(FVector{ 0.f, 10.f, 0.f });
	ColliderEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Collider End"));
	ColliderEnd->SetupAttachment(Mesh);
	ColliderEnd->SetRelativeLocation(FVector{ 0.f, 100.f, 0.f });

	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeapon_Katana::OnBoxOverlapBegin);
}

void ASSWeapon_Katana::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
