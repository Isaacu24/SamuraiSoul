// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Item/Weapon/SSWeapon_Katana.h"
#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include "Character/SSCharacterBase.h"
#include <Components/CapsuleComponent.h>

#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystemComponent.h"
#include "Abilities/SSGameplayAbility_Executed.h"

USSCombatComponent::USSCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Hit.AM_Hit'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EXECUTION_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Execution.AM_Execution'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EXECUTED_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Executed.AM_Executed'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PARRY_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Parry.AM_Parry'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> REBOUND_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Rebound.AM_Rebound'"));

	if (true == EXECUTION_MONTAGE.Succeeded())
	{
		ExecutionMontage = EXECUTION_MONTAGE.Object;
	}

	if (true == EXECUTED_MONTAGE.Succeeded())
	{
		ExecutedMontage = EXECUTED_MONTAGE.Object;
	}

	if (true == HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}

	if (true == PARRY_MONTAGE.Succeeded())
	{
		ParryMontage = PARRY_MONTAGE.Object;
	}

	if (true == REBOUND_MONTAGE.Succeeded())
	{
		ReboundMontage = REBOUND_MONTAGE.Object;
	}

	static ConstructorHelpers::FClassFinder<UGameplayAbility> ExecutedAbilityClass(TEXT("/Script/Engine.Blueprint'/Game/MyContent/Abilities/BP_SSGameplayAbility_Executed.BP_SSGameplayAbility_Executed_C'"));

	if (ExecutedAbilityClass.Succeeded())
	{
		ExecutedAbility = ExecutedAbilityClass.Class;
	}
}

void USSCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	HitEvent.BindUObject(this, &ThisClass::Hit);
	DeathEvent.BindUObject(this, &ThisClass::Die);
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
		Weapon->SetOwner(GetOwner());
		Weapon->Equip(InParent, InSocketName);
		OffWeapon();
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

void USSCombatComponent::SetEnemyWeapon()
{
	Weapon->SetEnemyWeapon();
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
}

void USSCombatComponent::ChangeDefenseType(EDefenseType Type) 
{
	DefenseBarrier->ChangeDefenseType(Type);
}

void USSCombatComponent::OnWeapon()
{
	if (nullptr == Weapon)
	{
		return;
	}

	Weapon->CollisionHiddenInGame(true);
	Weapon->SetActorEnableCollision(true);
	Weapon->SetActorTickEnabled(true);
}

void USSCombatComponent::OffWeapon()
{
	if (nullptr == Weapon)
	{	
		return;
	}

	Weapon->CollisionHiddenInGame(false);
	Weapon->SetActorEnableCollision(false);
	Weapon->SetActorTickEnabled(false);
}

void USSCombatComponent::Hit()
{
	if (true == IsRebound)
	{
		ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

		if (nullptr == Character)
		{
			return;
		}

		UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();

		if (nullptr != AbilitySystemComponent)
		{
			if (nullptr == ExecutedAbility)
			{
				return;
			}

			FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(ExecutedAbility);

			if (nullptr == AbilitySpec)
			{
				return;
			}

			AbilitySystemComponent->CancelAbilities();
			AbilitySystemComponent->TryActivateAbility(AbilitySpec->Handle);
		}
	}

	else
	{

	}

	//ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	//if (nullptr != Character)
	//{
	//	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	//	if (nullptr != AnimInstance)
	//	{
	//		AnimInstance->Montage_Play(HitMontage);
	//	}
	//}

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

	//		}
	//	}
	//}
}

void USSCombatComponent::Die()
{
	//Play Death Montage
}

void USSCombatComponent::ChangeRagdoll()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	USkeletalMeshComponent* MyMesh = Character->GetMesh();

	if (!MyMesh)
	{
		return;
	}

	MyMesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));

	MyMesh->SetSimulatePhysics(true);
	MyMesh->WakeAllRigidBodies();

	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MyMesh->AddImpulse((Character->GetVelocity() / 2.f) * MyMesh->GetMass());
	MyMesh->AddRadialImpulse(Character->GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
}

void USSCombatComponent::Parry(AActor* Opponent)
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());
	Enemy = Opponent;

	if (nullptr != Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			AnimInstance->Montage_Play(ParryMontage);

			IsParry = true;
			FOnMontageEnded ParryEndDelegate;
			ParryEndDelegate.BindUObject(this, &USSCombatComponent::ParryEnd);
			AnimInstance->Montage_SetEndDelegate(ParryEndDelegate, ParryMontage);
		}
	}
}

void USSCombatComponent::Rebound(AActor* Opponent)
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr != Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			AnimInstance->Montage_Play(ReboundMontage);
			
			IsRebound = true;
			FOnMontageEnded ReboundEndDelegate;
			ReboundEndDelegate.BindUObject(this, &USSCombatComponent::ReboundEnd);
			AnimInstance->Montage_SetEndDelegate(ReboundEndDelegate, ReboundMontage);
		}
	}
}

void USSCombatComponent::ParryEnd(UAnimMontage* Montage, bool bInterrupted)
{
	IsParry = false;
}

void USSCombatComponent::ReboundEnd(UAnimMontage* Montage, bool bInterrupted)
{
	IsRebound = false;
}
