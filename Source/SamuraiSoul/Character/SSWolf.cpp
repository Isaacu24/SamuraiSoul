// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSWolf.h"

#include "Component/SSCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interface/SSCombatableInterface.h"

ASSWolf::ASSWolf()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_BODY(TEXT("/Script/Engine.SkeletalMesh'/Game/Wolf/Wolf/Meshes/Wolf.Wolf'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Wolf/AB_SSWolf.AB_SSWolf_C'"));

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMeshComponent"));

	if (true == SK_BODY.Succeeded())
	{
		SkeletalMeshComponent->SetSkeletalMesh(SK_BODY.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		SkeletalMeshComponent->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	RootComponent = SkeletalMeshComponent;
	SkeletalMeshComponent->SetCollisionProfileName("NoCollision");

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileComponent->SetAutoActivate(false);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(SkeletalMeshComponent);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASSWolf::OnCapsuleBeginOverlap);
	CapsuleComponent->OnComponentHit.AddDynamic(this, &ASSWolf::OnCapsuleHit);
	CapsuleComponent->SetCollisionProfileName(TEXT("Wolf"));

	SpawnedFXComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("SpawnedFXComponent"));
	SpawnedFXComponent->SetupAttachment(SkeletalMeshComponent);
}

void ASSWolf::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSWolf::RunWolf(AActor* InActor)
{
	CapsuleComponent->IgnoreActorWhenMoving(InActor, true);

	ProjectileComponent->InitialSpeed = 1000.f;
	ProjectileComponent->MaxSpeed     = 1500.f;

	ProjectileComponent->Velocity = InActor->GetActorForwardVector() * 1000.f;
	ProjectileComponent->Activate();

	SkeletalMeshComponent->GetAnimInstance()->Montage_Play(RunMontage);

	ISSCombatableInterface* CombatPawn = Cast<ISSCombatableInterface>(InActor);

	if (nullptr != CombatPawn)
	{
		OnWolfOverlap.BindUObject(CombatPawn->GetCombatComponent(), &USSCombatComponent::Attack);
	}
}

void ASSWolf::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                           const FHitResult& Hit)
{
	if (nullptr != SpawnedFX)
	{
		SpawnedFXComponent = UGameplayStatics::SpawnEmitterAtLocation(
		                                                              GetWorld(),
		                                                              SpawnedFX,
		                                                              GetActorTransform()
		                                                             );
	}

	Destroy();
}

void ASSWolf::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                    bool bFromSweep, const FHitResult& SweepResult)
{
	if (nullptr != SpawnedFX)
	{
		SpawnedFXComponent = UGameplayStatics::SpawnEmitterAtLocation(
		                                                              GetWorld(),
		                                                              SpawnedFX,
		                                                              GetActorTransform()
		                                                             );
	}

	OnWolfOverlap.ExecuteIfBound(OtherActor, SweepResult);

	Destroy();
}
