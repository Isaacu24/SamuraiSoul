// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include <Components/BoxComponent.h>
#include <Interface/SSCombatableInterface.h>
#include "Component/SSCombatComponent.h"

ASSWeapon_DefenseBarrier::ASSWeapon_DefenseBarrier()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collider"));
	WeaponCollider->SetupAttachment(Mesh);
	WeaponCollider->SetRelativeLocation(FVector{0.f, 0.f, 20.f});
	WeaponCollider->SetRelativeRotation(FRotator{0.f, 90.f, 0.f});
	WeaponCollider->SetBoxExtent(FVector{75.f, 5.f, 100.f});

	WeaponCollider->SetCollisionProfileName("SSWeapon");
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponCollider->bHiddenInGame = false;

	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeapon_DefenseBarrier::OnBoxOverlapBegin);

	WeaponType = EWeaponType::Defense;
}

void ASSWeapon_DefenseBarrier::ChangeDefenseState(EDefenseState Type)
{
	DefenseType = Type;
}

bool ASSWeapon_DefenseBarrier::CheckAttackDirection(FVector A, FVector B)
{
	float ReturnValue = FVector::DotProduct(A, B);
	GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Blue, FString::SanitizeFloat(ReturnValue));

	if (0.5f <= ReturnValue)
	{
		return false;
	}

	return true;
}

void ASSWeapon_DefenseBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != GetOwner())
	{
		//Delegate
		FVector BarrierPos  = GetOwner()->GetActorForwardVector() * 75.f;
		FRotator BarrierRot = GetOwner()->GetActorRotation();
		SetActorLocation(GetOwner()->GetActorLocation() + BarrierPos);
		SetActorRotation(BarrierRot);
	}
}

void ASSWeapon_DefenseBarrier::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWeapon_DefenseBarrier::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
                                                 bool bFromSweep, const FHitResult& SweepResult)
{
	switch (DefenseType)
	{
		case EDefenseState::Defense:
			{
				FVector A = GetOwner()->GetActorForwardVector();
				A.Normalize();

				FVector B = OtherActor->GetOwner()->GetActorForwardVector();
				B.Normalize();

				if (false == CheckAttackDirection(A, B))
				{
					return;
				}

				ASSWeapon* Weapon = Cast<ASSWeapon>(OtherActor);

				if (nullptr != Weapon)
				{
					ISSCombatableInterface* MyOwner = Cast<ISSCombatableInterface>(GetOwner());
					ISSCombatableInterface* Enemy   = Cast<ISSCombatableInterface>(OtherActor->GetOwner());

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
							Enemy->GetCombatComponent()->OffWeapon();
							//MyOwner->GetCombatComponent()->DefenseHit();?
						}
					}
				}
			}
			break;
		case EDefenseState::Parry:
			{
				FVector A = GetOwner()->GetActorForwardVector();
				A.Normalize();

				FVector B = OtherActor->GetOwner()->GetActorForwardVector();
				B.Normalize();

				if (false == CheckAttackDirection(A, B))
				{
					return;
				}

				ASSWeapon* Weapon = Cast<ASSWeapon>(OtherActor);

				if (nullptr != Weapon)
				{
					ISSCombatableInterface* MyOwner = Cast<ISSCombatableInterface>(GetOwner());
					ISSCombatableInterface* Enemy   = Cast<ISSCombatableInterface>(OtherActor->GetOwner());

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
							MyOwner->GetCombatComponent()->Parry(OtherActor->GetOwner());

							Enemy->GetCombatComponent()->OffWeapon();
							Enemy->GetCombatComponent()->Rebound();
						}
					}
				}
			}
			break;
		default:
			break;
	}
}
