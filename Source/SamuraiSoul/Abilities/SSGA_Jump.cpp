// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGA_Jump.h"
#include <GameFramework/Character.h>
#include "SSGameplayTags.h"
#include "Interface/SSBehaviorInterface.h"

USSGA_Jump::USSGA_Jump()
{
	AbilityID = ESSAbilityID::Jump;

	//AbilityTags.AddTag(FSSGameplayTags::Get().Ability_JumpTag);
	//ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_JumpTag);
	//BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_Jump::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->OwnerActor);

	if (nullptr != Character)
	{
		Character->Jump();
	}

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(Character);

	if (nullptr != BehaviorPawn)
	{
		BehaviorPawn->GetCharacterLandedEvnet().AddUObject(this, &USSGA_Jump::CancelAbilityFromLand);
	}
}

void USSGA_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGA_Jump::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                           const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_Jump::CancelAbilityFromLand()
{
	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
