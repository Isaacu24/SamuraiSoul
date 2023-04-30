// Fill out your copyright notice in the Description page of Project Settings.


#include "SSWeapon.h"
#include "DrawDebugHelpers.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "Character/SSSamuraiCharacter.h"
#include "Character/SSCharacterBase.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Character/SSEnemyCharacter.h"

// Sets default values
ASSWeapon::ASSWeapon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName("NoCollision");

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collider"));
	WeaponCollider->SetupAttachment(Mesh);
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	WeaponCollider->bHiddenInGame = false;

	ColliderStart = CreateDefaultSubobject<USceneComponent>(TEXT("Collider Start"));
	ColliderStart->SetupAttachment(Mesh);
	ColliderEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Collider End"));
	ColliderEnd->SetupAttachment(Mesh);

	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeapon::OnBoxOverlapBegin);
}

void ASSWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	if (nullptr != InParent)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(InParent, TransformRules, InSocketName);
	}
}

// Called when the game starts or when spawned
void ASSWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWeapon::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = ColliderStart->GetComponentLocation();
	const FVector End = ColliderEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore = {}; 
	ActorsToIgnore.Add(this);
	if (nullptr != GetOwner())
	{
		ActorsToIgnore.Add(GetOwner());
	}
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
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f
	);

	if (nullptr != OutHit.GetActor())
	{
		FString Name = OutHit.GetActor()->GetName();
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Weapon: "), *Name), true, true, FLinearColor(1.0, 0.0, 1.0));
		DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 25.f, 12, FColor::Green, false, 1.f);
	}
}

