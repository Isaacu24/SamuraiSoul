// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Item/Weapon/SSWeapon_Katana.h"
#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include "Character/SSCharacterBase.h"
#include <Components/CapsuleComponent.h>

USSCombatComponent::USSCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> EXECUTION_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Execution.AM_Execution'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EXECUTED_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Executed.AM_Executed'"));

	if (true == EXECUTION_MONTAGE.Succeeded())
	{
		ExecutionMontage = EXECUTION_MONTAGE.Object;
	}

	if (true == EXECUTED_MONTAGE.Succeeded())
	{
		ExecutedMontage = EXECUTED_MONTAGE.Object;
	}
}

void USSCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	HitEvent.BindUObject(this, &ThisClass::Hit);
	DeathEvent.BindUObject(this, &ThisClass::Die);

	ExecutionEvent.BindUObject(this, &ThisClass::Execution);
	ExecutedEvent.BindUObject(this, &ThisClass::Executed);
}

void USSCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USSCombatComponent::EquipWeapon(USceneComponent* InParent, FName InSocketName)
{
	Weapon = GetWorld()->SpawnActor<ASSWeapon_Katana>();

	if (nullptr != Weapon)
	{
		Weapon->Equip(InParent, InSocketName);
		Weapon->SetOwner(GetOwner());
	}
}

void USSCombatComponent::EquipDefenseBarrier()
{
	DefenseBarrier = GetWorld()->SpawnActor<ASSWeapon_DefenseBarrier>();

	if (nullptr != Weapon)
	{
		DefenseBarrier->SetOwner(GetOwner());
		OffDefense();
	}
}

void USSCombatComponent::OnDefense()
{
	if (nullptr == DefenseBarrier)
	{
		return;
	}

	DefenseBarrier->SetActorHiddenInGame(false);
	DefenseBarrier->SetActorEnableCollision(true);
	DefenseBarrier->SetActorTickEnabled(true);

	Weapon->SetActorHiddenInGame(true);
	Weapon->SetActorEnableCollision(false);
	Weapon->SetActorTickEnabled(false);
}

void USSCombatComponent::OffDefense()
{
	if (nullptr == DefenseBarrier)
	{
		return;
	}

	DefenseBarrier->SetActorHiddenInGame(true);
	DefenseBarrier->SetActorEnableCollision(false);
	DefenseBarrier->SetActorTickEnabled(false);

	Weapon->SetActorHiddenInGame(false);
	Weapon->SetActorEnableCollision(true);
	Weapon->SetActorTickEnabled(true);
}


void USSCombatComponent::Hit()
{
	//Play Hit Montage

	//if (0.f >= Attributes->GetHealth())
	//{
	//	return;
	//}

	//if (nullptr != AbilitySystemComponent
	//	&& nullptr != DamageEffect)
	//{
	//	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	//	EffectContext.AddSourceObject(this);

	//	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1, EffectContext);

	//	if (SpecHandle.IsValid())
	//	{
	//		FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	//		UE_LOG(LogTemp, Log, TEXT("Enemy HP: %f"), Attributes->GetHealth());

	//		if (0.f >= Attributes->GetHealth())
	//		{
	//			USkeletalMeshComponent* MyMesh = GetMesh();

	//			if (!MyMesh)
	//				return;

	//			MyMesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));

	//			MyMesh->SetSimulatePhysics(true);
	//			MyMesh->WakeAllRigidBodies();

	//			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//			//SetMovementMode(EMovementMode::MOVE_None);

	//			MyMesh->AddImpulse((GetVelocity() / 2.f)* MyMesh->GetMass());
	//			MyMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
	//		}
	//	}
	//}
}

void USSCombatComponent::Die()
{
	//Play Death Montage
}

void USSCombatComponent::Execution()
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr != Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			AnimInstance->Montage_Play(ExecutionMontage);
		}
	}
}

void USSCombatComponent::Executed()
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr != Character)
	{
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Executed"));
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			AnimInstance->Montage_Play(ExecutedMontage);
		}
	}
}
