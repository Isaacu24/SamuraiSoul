// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Execution.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/SSCharacterBase.h"
#include <MotionWarpingComponent.h>
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatableInterface.h"
#include "SSGameplayTags.h"
#include "Math/RandomStream.h"

USSGameplayAbility_Execution::USSGameplayAbility_Execution()
{
	AbilityID = ESSAbilityID::Execution;

	AbilityTags.AddTag(FSSGameplayTags::Get().DeferredAbility_ExecutionTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().DeferredAbility_ExecutionTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().DeferredAbilityTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
	ActivationRequiredTags.AddTag(FSSGameplayTags::Get().Ability_ParryTag);
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

	ASSCharacterBase* Character            = Cast<ASSCharacterBase>(ActorInfo->OwnerActor);
	ISSCombatableInterface* CombatablePawn = Cast<ISSCombatableInterface>(Character);

	if (false == CombatablePawn->GetCanEnemyExecution())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	CombatablePawn->SetCanEnemyExecution(false);

	AActor* ExecutionTarget                 = CombatablePawn->GetCombatComponent()->GetTarget();
	ISSCombatableInterface* CombatableEnemy = Cast<ISSCombatableInterface>(ExecutionTarget);

	check(ExecutionTarget);
	check(CombatableEnemy);

	FMotionWarpingTarget Target = {};
	Target.Name                 = FName("Target");
	Target.Location             = ExecutionTarget->GetActorLocation();
	Target.Rotation             = ExecutionTarget->GetActorRotation();
	Target.Rotation.Yaw += 180.f;

	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target);
	CombatablePawn->GetCombatComponent()->SetTarget(nullptr);

	int32 RandomNumber = FMath::RandRange(0, ExecutionMontages.Num() - 1);
	check(ExecutionMontages[RandomNumber]);

	PlayMontage(ExecutionMontages[RandomNumber], Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Warning, TEXT("Random Number: %d"), RandomNumber);

	CombatableEnemy->GetCombatComponent()->BeExecuted(RandomNumber);
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
