// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/SSCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Item/Weapon/SSWeapon_Katana.h"
#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include "Character/SSCharacterBase.h"
#include "Component/SSCharacterStatComponent.h"

#include "AbilitySystemComponent.h"
#include "Abilities/SSGameplayAbility.h"
#include "Interface/SSCombatInterface.h"
#include "AbilitySystemInterface.h"
#include "SSGameplayTags.h"

USSCombatComponent::USSCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USSCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != Weapon)
	{
		Weapon->OnWeaponOverlap.BindUObject(this, &USSCombatComponent::Attack);
	}
}

void USSCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USSCombatComponent::EquipWeapon(EWeaponType Type, USceneComponent* InParent, FName InSocketName)
{
	switch (Type)
	{
		case EWeaponType::None:
			break;

		case EWeaponType::Katana:
			Weapon = GetWorld()->SpawnActor<ASSWeapon_Katana>();

			if (nullptr != Weapon)
			{
				Weapon->SetOwner(GetOwner());
				Weapon->Equip(InParent, InSocketName);
				OffWeapon();
			}
			break;

		case EWeaponType::Bow:
			break;
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

void USSCombatComponent::ActivateAbility(const TSubclassOf<UGameplayAbility> Ability) const
{
	if (nullptr == Ability)
	{
		return;
	}

	IAbilitySystemInterface* Character = Cast<IAbilitySystemInterface>(GetOwner());

	if (nullptr == Character)
	{
		return;
	}

	UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();

	if (nullptr != AbilitySystemComponent)
	{
		const FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Ability);

		if (nullptr == AbilitySpec)
		{
			return;
		}

		AbilitySystemComponent->CancelAbilities();
		AbilitySystemComponent->TryActivateAbility(AbilitySpec->Handle);
	}
}

void USSCombatComponent::TakeDamageEffect(const TSubclassOf<UGameplayEffect> Effect) const
{
	if (nullptr == Effect)
	{
		return;
	}

	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr == Character)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = Character->GetAbilitySystemComponent()->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = Character->GetAbilitySystemComponent()->
	                                                        MakeOutgoingSpec(Effect, 1, EffectContext);

	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle GEHandle = Character->GetAbilitySystemComponent()->
		                                                  ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		//Character->GetStatComponent()->OnHPChanged.Broadcast(Character->GetStatComponent()->GetHealth());

		if (0.f >= Character->GetStatComponent()->GetHealth())
		{
			Character->Die();
		}
	}
}

void USSCombatComponent::OnDefense() const
{
	if (nullptr == DefenseBarrier)
	{
		return;
	}

	DefenseBarrier->SetActorHiddenInGame(false);
	DefenseBarrier->SetActorEnableCollision(true);
	DefenseBarrier->SetActorTickEnabled(true);
}

void USSCombatComponent::OffDefense() const
{
	if (nullptr == DefenseBarrier)
	{
		return;
	}

	DefenseBarrier->SetActorHiddenInGame(true);
	DefenseBarrier->SetActorEnableCollision(false);
	DefenseBarrier->SetActorTickEnabled(false);
}

void USSCombatComponent::ChangeDefenseState(EDefenseState Type) const
{
	DefenseBarrier->ChangeDefenseState(Type);
}

void USSCombatComponent::OnWeapon() const
{
	if (nullptr == Weapon)
	{
		return;
	}

	Weapon->CollisionHiddenInGame(true);
	Weapon->SetActorEnableCollision(true);
	Weapon->SetActorTickEnabled(true);
}

void USSCombatComponent::OffWeapon() const
{
	if (nullptr == Weapon)
	{
		return;
	}

	Weapon->CollisionHiddenInGame(false);
	Weapon->SetActorEnableCollision(false);
	Weapon->SetActorTickEnabled(false);
}

void USSCombatComponent::Attack(AActor* InActor, const FHitResult& HitResult) const
{
	const ISSCombatInterface* MyOwner = Cast<ISSCombatInterface>(GetOwner());
	const ISSCombatInterface* Enemy   = Cast<ISSCombatInterface>(InActor);

	if (nullptr == MyOwner
		|| nullptr == Enemy)
	{
		return;
	}

	if (MyOwner != Enemy)
	{
		Enemy->GetCombatComponent()->Hit(GetOwner());
	}
}

void USSCombatComponent::Hit(AActor* InActor)
{
	/*ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());
	ASSCharacterBase* Enemy     = Cast<ASSCharacterBase>(InActor);

	if (true == IsRebound)
	{
		if (nullptr == Character)
		{
			return;
		}

		FGameplayEventData Payload;
		Payload.EventTag = FSSGameplayTags::Get().BeExecutedTag;

		Character->GetAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
	}

	else
	{
		if (nullptr == Enemy
			|| nullptr == Character)
		{
			return;
		}

		FVector A = Character->GetActorForwardVector();
		A.Normalize();
		FVector B = Enemy->GetActorForwardVector();
		B.Normalize();

		const float ReturnValue = FVector::DotProduct(A, B);

		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (0.0f <= ReturnValue)
		{
			if (nullptr != AnimInstance)
			{
				AnimInstance->Montage_Play(HitBackMontage);

				FOnMontageEnded HitEndDelegate;
				HitEndDelegate.BindUObject(this, &USSCombatComponent::HitEnd);
				AnimInstance->Montage_SetEndDelegate(HitEndDelegate, HitBackMontage);
			}
		}

		else
		{
			if (nullptr != AnimInstance)
			{
				AnimInstance->Montage_Play(HitForwardMontage);

				FOnMontageEnded HitEndDelegate;
				HitEndDelegate.BindUObject(this, &USSCombatComponent::HitEnd);
				AnimInstance->Montage_SetEndDelegate(HitEndDelegate, HitForwardMontage);
			}
		}
	}*/

	TakeDamageEffect(DamageEffect);
}

void USSCombatComponent::Parry(AActor* Opponent)
{
	const ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	Target = Opponent;

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
	const ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

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

void USSCombatComponent::HitEnd(UAnimMontage* Montage, bool bInterrupted)
{
	const ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr != Character)
	{
		Character->GetAbilitySystemComponent()->RemoveReplicatedLooseGameplayTag(FSSGameplayTags::Get().HitTag);
	}
}
