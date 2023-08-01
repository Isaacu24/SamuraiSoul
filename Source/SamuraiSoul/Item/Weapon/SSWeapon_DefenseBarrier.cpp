// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include <Components/BoxComponent.h>
#include <Interface/SSCombatableInterface.h>
#include <Interface/SSBehaviorInterface.h>
#include "Component/SSCombatComponent.h"
#include "Components/CapsuleComponent.h"

ASSWeapon_DefenseBarrier::ASSWeapon_DefenseBarrier()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	BarrierCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Barrier Collider"));
	BarrierCollider->SetupAttachment(Mesh);
	BarrierCollider->SetRelativeLocation(FVector{-30.f, 0.f, 0.f});
	BarrierCollider->SetRelativeRotation(FRotator{0.f, 90.f, 0.f});
	BarrierCollider->SetCapsuleHalfHeight(120.f);
	BarrierCollider->SetCapsuleRadius(80.f);

	BarrierCollider->SetCollisionProfileName("Barrier");
	BarrierCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//BarrierCollider->bHiddenInGame = false;

	BarrierCollider->OnComponentBeginOverlap.AddDynamic(this, &ASSWeapon_DefenseBarrier::OnWeaponOverlapBegin);

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

	if (0.0f <= ReturnValue)
	{
		return false;
	}

	return true;
}

void ASSWeapon_DefenseBarrier::Defense(AActor* OtherActor)
{
	ASSWeapon* Weapon = Cast<ASSWeapon>(OtherActor);

	if (nullptr == Weapon
		|| EAttackType::SpecialAttack == Weapon->GetAttackType())
	{
		return;
	}

	FVector A = GetOwner()->GetActorForwardVector();
	A.Normalize();

	FVector B = Weapon->GetOwner()->GetActorForwardVector();
	B.Normalize();

	if (false == CheckAttackDirection(A, B))
	{
		return;
	}

	ISSCombatableInterface* MyOwner = Cast<ISSCombatableInterface>(GetOwner());
	ISSCombatableInterface* Enemy   = Cast<ISSCombatableInterface>(Weapon->GetOwner());

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
			OnHitEvent.ExecuteIfBound();

			Enemy->GetCombatComponent()->OffWeapon();
			MyOwner->GetCombatComponent()->DefenseHit();
		}
	}
}

void ASSWeapon_DefenseBarrier::Parry(AActor* OtherActor)
{
	ASSWeapon* Weapon = Cast<ASSWeapon>(OtherActor);

	if (nullptr == Weapon)
	{
		return;
	}

	ISSCombatableInterface* CombatPawn  = Cast<ISSCombatableInterface>(GetOwner());
	ISSCombatableInterface* CombatEnemy = Cast<ISSCombatableInterface>(Weapon->GetOwner());

	ISSBehaviorInterface* BehaviorEnemy = Cast<ISSBehaviorInterface>(OtherActor->GetOwner());

	if (nullptr == BehaviorEnemy)
	{
		return;
	}

	switch (Weapon->GetAttackType())
	{
		case EAttackType::Normal:
			if (false == BehaviorEnemy->IsDown())
			{
				CombatPawn->SetCanEnemyExecution(false);
			}
			else
			{
				CombatPawn->SetCanEnemyExecution(true);
			}
			break;

		case EAttackType::SpecialAttack:
			if (false == BehaviorEnemy->IsDown())
			{
				Defense(OtherActor);
				return;
			}
			break;
	}

	FVector A = GetOwner()->GetActorForwardVector();
	A.Normalize();

	FVector B = Weapon->GetOwner()->GetActorForwardVector();
	B.Normalize();

	if (false == CheckAttackDirection(A, B))
	{
		return;
	}

	if (nullptr != CombatPawn
		&& nullptr != CombatEnemy)
	{
		if (CombatPawn == CombatEnemy)
		{
			return;
		}

		if (nullptr != CombatPawn->GetCombatComponent()
			&& nullptr != CombatEnemy->GetCombatComponent())
		{
			CombatPawn->GetCombatComponent()->Parry(OtherActor->GetOwner());

			CombatEnemy->GetCombatComponent()->OffWeapon();
			CombatEnemy->GetCombatComponent()->Rebound();
		}
	}
}

void ASSWeapon_DefenseBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != GetOwner())
	{
		//Delegate
		FVector BarrierPos  = GetOwner()->GetActorForwardVector() * 50.f;
		FRotator BarrierRot = GetOwner()->GetActorRotation();
		SetActorLocation(GetOwner()->GetActorLocation() + BarrierPos);
		SetActorRotation(BarrierRot);
	}
}

void ASSWeapon_DefenseBarrier::BeginPlay()
{
	Super::BeginPlay();
}

void ASSWeapon_DefenseBarrier::OnWeaponOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
                                                    bool bFromSweep, const FHitResult& SweepResult)
{
	switch (DefenseType)
	{
		case EDefenseState::Defense:
			{
				Defense(OtherActor);
			}
			break;
		case EDefenseState::Parry:
			{
				Parry(OtherActor);
			}
			break;
	}
}
