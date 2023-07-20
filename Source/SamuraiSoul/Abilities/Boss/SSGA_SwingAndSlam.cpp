// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Boss/SSGA_SwingAndSlam.h"
#include "SSGameplayTags.h"
#include "Interface/SSCharacterAIInterface.h"

USSGA_SwingAndSlam::USSGA_SwingAndSlam()
{
	AbilityID = ESSAbilityID::SwingAndSlam;

	//AbilityTags.AddTag(FSSGameplayTags::Get().Ability_SwingAndSlamTag);
	//ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_SwingAndSlamTag);
	//ActivationBlockedTags.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_SwingAndSlam::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGA_SwingAndSlam::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGA_SwingAndSlam::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(SwingAndSlamMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGA_SwingAndSlam::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(ActorInfo->AvatarActor);

	if (nullptr != AI)
	{
		AI->AttackEnd();
	}
}

void USSGA_SwingAndSlam::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGA_SwingAndSlam::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
