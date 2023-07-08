// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Boss/SSGA_HandAndSwordSwing.h"
#include "SSGameplayTags.h"
#include "Interface/SSCharacterAIInterface.h"

USSGA_HandAndSwordSwing::USSGA_HandAndSwordSwing()
{
	AbilityID = ESSAbilityID::HandAndSwordSwing;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_HandAndSwordSwingTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_HandAndSwordSwingTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_HandAndSwordSwing::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGA_HandAndSwordSwing::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGA_HandAndSwordSwing::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(HandAndSwordSwingMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGA_HandAndSwordSwing::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(ActorInfo->AvatarActor);

	if (nullptr != AI)
	{
		AI->AttackEnd();
	}
}

void USSGA_HandAndSwordSwing::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_HandAndSwordSwing::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
