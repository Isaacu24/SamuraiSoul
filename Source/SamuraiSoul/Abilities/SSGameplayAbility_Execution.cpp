// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Execution.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/SSCharacterBase.h"
#include <MotionWarpingComponent.h>
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatInterface.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Execution::USSGameplayAbility_Execution()
{
	AbilityID      = ESSAbilityID::Execution;
	AbilityInputID = ESSAbilityInputID::Attack;

	AbilityTags.AddTag(FSSGameplayTags::Get().DeferredAbility_ExecutionTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().DeferredAbility_ExecutionTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().DeferredAbilityTag);
}

void USSGameplayAbility_Execution::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Execution::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Execution::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSCharacterBase* Character    = Cast<ASSCharacterBase>(ActorInfo->OwnerActor);
	ISSCombatInterface* Combatable = Cast<ISSCombatInterface>(ActorInfo->OwnerActor);

	if (nullptr == Character
		|| nullptr == Combatable)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* ExecutionTarget = Combatable->GetCombatComponent()->GetTarget();

	if (nullptr != ExecutionTarget)
	{
		FMotionWarpingTarget Target = {};
		Target.Name                 = FName("Target");
		Target.Location             = ExecutionTarget->GetActorLocation();
		Target.Rotation             = ExecutionTarget->GetActorRotation();
		Target.Rotation.Yaw += 180.f;

		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target);
		Combatable->GetCombatComponent()->SetTarget(nullptr);
	}

	PlayMontage(ExecutionMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Execution::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Execution::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Execution::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
}
