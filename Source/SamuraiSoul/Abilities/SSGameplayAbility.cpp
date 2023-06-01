// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

USSGameplayAbility::USSGameplayAbility()
{
}

void USSGameplayAbility::AbilityCompleted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void USSGameplayAbility::AbilityBlendOut(FGameplayTag EventTag, FGameplayEventData Payload)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void USSGameplayAbility::AbilityInterrupted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void USSGameplayAbility::AbilityCancelled(FGameplayTag EventTag, FGameplayEventData Payload)
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void USSGameplayAbility::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}

void USSGameplayAbility::CancelAllAbility()
{
	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetActorInfo().AvatarActor);
	UAbilitySystemComponent* ASC         = AbilityPawn->GetAbilitySystemComponent();
	ASC->CancelAbility(this);
}
