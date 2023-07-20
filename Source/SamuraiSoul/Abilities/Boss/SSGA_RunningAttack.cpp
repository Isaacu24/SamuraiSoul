// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Boss/SSGA_RunningAttack.h"
#include "SSGameplayTags.h"
#include "Interface/SSCharacterAIInterface.h"

USSGA_RunningAttack::USSGA_RunningAttack()
{
	AbilityID = ESSAbilityID::RunningAttack;

	//AbilityTags.AddTag(FSSGameplayTags::Get().Ability_RunningAttackTag);
	//ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_RunningAttackTag);
	//BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_RunningAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGA_RunningAttack::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGA_RunningAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(RunningAttackMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGA_RunningAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(ActorInfo->AvatarActor);

	if (nullptr != AI)
	{
		AI->AttackEnd();
	}
}

void USSGA_RunningAttack::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_RunningAttack::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
