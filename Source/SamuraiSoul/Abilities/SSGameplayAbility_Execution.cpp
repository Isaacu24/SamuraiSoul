// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Execution.h"
#include <Kismet/KismetSystemLibrary.h>
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/SSCharacterBase.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatInterface.h"

USSGameplayAbility_Execution::USSGameplayAbility_Execution()
{
	AbilityID      = ESSAbilityID::Execution;
	AbilityInputID = ESSAbilityInputID::Execution;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Execution")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Execution")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_Execution::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputPressed: %s"), *GetName()));
}

void USSGameplayAbility_Execution::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputReleased: %s"), *GetName()));
}

void USSGameplayAbility_Execution::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSCharacterBase* Character    = Cast<ASSCharacterBase>(ActorInfo->OwnerActor);
	ISSCombatInterface* Combatable = Cast<ISSCombatInterface>(Character);

	if (nullptr == Character
		&& nullptr == Combatable)
	{
		return;
	}

	if (nullptr != Combatable->GetCombatComponent()->GetTarget())
	{
		FMotionWarpingTarget Target = {};
		Target.Name                 = FName("Target");
		Target.Location             = Combatable->GetCombatComponent()->GetTarget()->GetActorLocation();
		Target.Rotation             = Combatable->GetCombatComponent()->GetTarget()->GetActorRotation();
		Target.Rotation.Yaw += 180.f;

		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target);
		Combatable->GetCombatComponent()->SetTarget(nullptr);
	}

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != ExecutionMontage)
		{
			USSAbilityTask_PlayMontageAndWait* Task
				= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, ExecutionMontage, FGameplayTagContainer(), 1.f, NAME_None,
				                                                                false);

			Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
			Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
			Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
			Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
			Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

			Task->ReadyForActivation();
		}
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ActivateAbility: %s"), *GetName()));
}

void USSGameplayAbility_Execution::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_Execution::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}

void USSGameplayAbility_Execution::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
