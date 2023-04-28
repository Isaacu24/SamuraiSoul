// Fill out your copyright notice in the Description page of Project Settings.


#include "SSWeaponActor.h"
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "../Character/SSSamuraiCharacter.h"
#include "../Character/SSCharacterBase.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
ASSWeaponActor::ASSWeaponActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collider"));
	WeaponCollider->SetupAttachment(Mesh);
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	ColliderStart = CreateDefaultSubobject<USceneComponent>(TEXT("Collider Start"));
	ColliderStart->SetupAttachment(Mesh);
	ColliderEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Collider End"));
	ColliderEnd->SetupAttachment(Mesh);

	//Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	//Sphere->SetupAttachment(Mesh);

	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeaponActor::OnBoxOverlapBegin);
	//Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASSWeaponActor::OnSphereOverlapBegin);
}

// Called when the game starts or when spawned
void ASSWeaponActor::BeginPlay()
{
	Super::BeginPlay();	
}

void ASSWeaponActor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = ColliderStart->GetComponentLocation();
	const FVector End = ColliderEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore = {}; 
	ActorsToIgnore.Add(this);
	FHitResult OutHit;

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
		true
	);
}

//void ASSWeaponActor::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	ASSCharacterBase* Character = Cast<ASSCharacterBase>(OtherActor);
//
//	if (nullptr != Character)
//	{
//		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
//		AttachToComponent(Character->GetMesh(), TransformRules, FName("Weapon_rSocket"));
//	}
//}
//
