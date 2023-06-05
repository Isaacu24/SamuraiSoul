// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "SSAbilityTask_PlayMontageAndWait.h"

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

void USSGameplayAbility::PlayMontage(UAnimMontage* Montage, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != Montage)
		{
			USSAbilityTask_PlayMontageAndWait* Task
				= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, Montage, FGameplayTagContainer(), 1.f, NAME_None,
				                                                                false);

			Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
			Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
			Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
			Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
			Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

			Task->ReadyForActivation();
		}
	}
}
