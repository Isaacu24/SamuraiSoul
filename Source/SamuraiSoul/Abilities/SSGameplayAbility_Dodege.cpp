// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Dodege.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Interface/SSBehaviorInterface.h"
#include "SSGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

USSGameplayAbility_Dodege::USSGameplayAbility_Dodege()
{
	AbilityID = ESSAbilityID::Dodge;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_DodgeTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_DodgeTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_Dodege::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Dodege::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Dodege::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MyCharacter = Cast<ACharacter>(ActorInfo->AvatarActor);

	if (nullptr == MyCharacter)
	{
		return;
	}

	MyCollisionProfileName = MyCharacter->GetCapsuleComponent()->GetCollisionProfileName();
	MyCharacter->GetCapsuleComponent()->SetCollisionProfileName("DodgeCharacter");

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(ActorInfo->OwnerActor);

	if (nullptr == BehaviorPawn
		|| false == BehaviorPawn->IsEquip())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const FVector2D MovementVector = BehaviorPawn->GetMovementVector();

	EDirection Direction = EDirection::Foward;

	if (true == BehaviorPawn->IsLockOn())
	{
		if (0.9f <= MovementVector.Y)
		{
			Direction = EDirection::Foward;
		}

		else if (-0.9f >= MovementVector.Y)
		{
			Direction = EDirection::Back;
		}

		else if (0.9f <= MovementVector.X)
		{
			Direction = EDirection::Right;
		}

		else
		{
			Direction = EDirection::Left;
		}
	}

	PlayMontage(DodgeMontages[static_cast<int>(Direction)], Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Dodege::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (nullptr == MyCharacter)
	{
		return;
	}

	MyCharacter->GetCapsuleComponent()->SetCollisionProfileName(MyCollisionProfileName);
}

void USSGameplayAbility_Dodege::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Dodege::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
