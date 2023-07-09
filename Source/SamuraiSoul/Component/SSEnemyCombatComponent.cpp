// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSEnemyCombatComponent.h"
#include "GameplayEffect.h"
#include "SSGameplayTags.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Item/Weapon/SSWeapon.h"

USSEnemyCombatComponent::USSEnemyCombatComponent()
{
}

void USSEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USSEnemyCombatComponent::AttackByAI() const
{
	switch (Weapon->GetWeaponType())
	{
		case EWeaponType::Katana:
			TryActivateAbility(FSSGameplayTags::Get().Ability_SlashTag);
			break;
		case EWeaponType::Bow:
			// Active Ability
			break;
		default:
			break;
	}
}

void USSEnemyCombatComponent::EquipUnarm()
{
	TryActivateAbility(FSSGameplayTags::Get().Ability_EquipUnarmTag);
}

void USSEnemyCombatComponent::Parry(AActor* InActor)
{
	Super::Parry(InActor);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetParry(true);
}

void USSEnemyCombatComponent::Rebound()
{
	Super::Rebound();

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetRebound(true);
}

void USSEnemyCombatComponent::Defense()
{
	TryActivateAbility(FSSGameplayTags::Get().Ability_DefenseTag);
}

void USSEnemyCombatComponent::Hit(EAttackType InType)
{
	Super::Hit(InType);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetHit(true);
	AIPawn->HidePerilousMark();
}

void USSEnemyCombatComponent::BeExecuted(int8 RandomNumber)
{
	Super::BeExecuted(RandomNumber);

	ExecutionNumber = RandomNumber;

	ensure(BeExecutedEffect);
	TakeGameplayEffect(BeExecutedEffect);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(GetOwner());
	AIPawn->SetBeExecuted(true);
}

void USSEnemyCombatComponent::BeAssassinated(int8 RandomNumber)
{
	Super::BeExecuted(RandomNumber);

	AssassinationNumber = RandomNumber;

	ensure(BeAssassinatedEffect);
	TakeGameplayEffect(BeAssassinatedEffect);
}
