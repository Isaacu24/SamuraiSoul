// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Defense.h"
#include <GameFramework/Character.h>
#include "SSAbilityTask.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatInterface.h"

USSGameplayAbility_Defense::USSGameplayAbility_Defense()
{
	AbilityID      = ESSAbilityID::Defense;
	AbilityInputID = ESSAbilityInputID::Defense;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Defense")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Defense")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_Defense::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Defense::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Defense::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const TWeakObjectPtr<AActor> Character = ActorInfo->OwnerActor;
	const ISSCombatInterface* Combatable   = Cast<ISSCombatInterface>(Character);

	if (nullptr == Character
		|| nullptr == Combatable)
	{
		return;
	}

	Combatable->GetCombatComponent()->OnDefense();

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != DefenseMontage
			&& nullptr != DefenseRootMontage)
		{
			if (0.1f <= ActorInfo->OwnerActor->GetVelocity().Size())
			{
				//Not Root Anim Montage
				USSAbilityTask_PlayMontageAndWait* Task
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, DefenseMontage, FGameplayTagContainer(), 1.f, NAME_None,
					                                                                false);

				Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
				Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
				Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
				Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
				Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

				Task->ReadyForActivation();
			}

			else
			{
				//Root Anim Montage
				USSAbilityTask_PlayMontageAndWait* Task
					= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, DefenseRootMontage, FGameplayTagContainer(), 1.f,
					                                                                NAME_None, false);

				Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
				Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
				Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
				Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
				Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

				Task->ReadyForActivation();
			}
		}
	}
}

void USSGameplayAbility_Defense::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ACharacter* Character          = Cast<ACharacter>(ActorInfo->OwnerActor);
	ISSCombatInterface* Combatable = Cast<ISSCombatInterface>(Character);

	if (nullptr != Character
		&& nullptr != Combatable)
	{
		Combatable->GetCombatComponent()->OffDefense();

		if (nullptr != Character->GetMesh()->GetAnimInstance())
		{
			Character->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseLEnd"), DefenseMontage);
			Character->GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseLEnd"), DefenseRootMontage);
		}
	}
}

void USSGameplayAbility_Defense::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Defense::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
