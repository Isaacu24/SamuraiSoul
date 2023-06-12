// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/SSCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Item/Weapon/SSWeapon_Katana.h"
#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include "Character/SSCharacterBase.h"
#include "Component/SSCharacterStatComponent.h"

#include "AbilitySystemComponent.h"
#include "Abilities/SSGameplayAbility.h"
#include "Interface/SSCombatableInterface.h"
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

void USSCombatComponent::TakeGameplayEffect(const TSubclassOf<UGameplayEffect> Effect) const
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
		Character->GetAbilitySystemComponent()->
		           ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
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


ASSWeapon_DefenseBarrier* USSCombatComponent::BindDefenseHit() const
{
	return DefenseBarrier;
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
	const ISSCombatableInterface* MyOwner = Cast<ISSCombatableInterface>(GetOwner());
	const ISSCombatableInterface* Enemy   = Cast<ISSCombatableInterface>(InActor);

	if (nullptr == MyOwner
		|| nullptr == Enemy)
	{
		return;
	}

	Enemy->GetCombatComponent()->Hit();

	//if (MyOwner != Enemy)
	//{
	//	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetOwner());

	//	// 현재 활성화된 어빌리티들 가져오기
	//	TArray<FGameplayAbilitySpec> ActiveAbilities = AbilityPawn->GetAbilitySystemComponent()->GetActivatableAbilities();

	//	// 각 어빌리티의 태그 출력
	//	for (const FGameplayAbilitySpec AbilitySpec : ActiveAbilities)
	//	{
	//		const FGameplayTagContainer& AbilityTags = AbilitySpec.Ability->AbilityTags;

	//		if (true == AbilityTags.HasTag(FSSGameplayTags::Get().DeferredAbility_ExecutionTag))
	//		{
	//			if (true == AbilitySpec.IsActive())
	//			{
	//				Enemy->GetCombatComponent()->BeExecuted();
	//			}

	//			else
	//			{
	//				Enemy->GetCombatComponent()->Hit();
	//			}
	//		}
	//	}
	//}
}

void USSCombatComponent::Parry(AActor* InActor)
{
	ensure(InActor);
	SetTarget(InActor);

	ensure(ParryAbility);
	ActivateAbility(ParryAbility);
}

void USSCombatComponent::Hit()
{
	ensure(DamageEffect);
	TakeGameplayEffect(DamageEffect);
}

void USSCombatComponent::BeExecuted(int8 RandomNumber)
{
	ExecutionNumber = RandomNumber;

	ensure(BeExecutedEffect);
	TakeGameplayEffect(BeExecutedEffect);
}

void USSCombatComponent::Rebound()
{
	ensure(ReboundEffect);
	TakeGameplayEffect(ReboundEffect);
}
