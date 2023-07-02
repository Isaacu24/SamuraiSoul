// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_Assassination.h"

#include "MotionWarpingComponent.h"
#include "RootMotionModifier.h"
#include "SSGameplayTags.h"
#include "Character/SSCharacterBase.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCombatableInterface.h"

USSGameplayAbility_Assassination::USSGameplayAbility_Assassination()
{
	AbilityID = ESSAbilityID::Assassination;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_AssassinationTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_AssassinationTag);
	BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGameplayAbility_Assassination::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Assassination::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                     const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Assassination::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                       const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSCharacterBase* Character            = Cast<ASSCharacterBase>(ActorInfo->OwnerActor);
	ISSCombatableInterface* CombatablePawn = Cast<ISSCombatableInterface>(Character);

	if (false == CombatablePawn->GetCanEnemyAssassination())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	CombatablePawn->SetCanEnemyAssassination(false);

	AActor* AssassinationTarget             = CombatablePawn->GetCombatComponent()->GetTarget();
	ISSCombatableInterface* CombatableEnemy = Cast<ISSCombatableInterface>(AssassinationTarget);

	check(AssassinationTarget);
	check(CombatableEnemy);

	FMotionWarpingTarget Target = {};
	Target.Name                 = FName("Target");
	Target.Location             = AssassinationTarget->GetActorLocation();
	Target.Rotation             = AssassinationTarget->GetActorRotation();

	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target);
	CombatablePawn->GetCombatComponent()->SetTarget(nullptr);

	int32 RandomNumber = FMath::RandRange(0, AssassinationMontages.Num() - 1);
	check(AssassinationMontages[RandomNumber]);

	PlayMontage(AssassinationMontages[RandomNumber], Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Warning, TEXT("Random Number: %d"), RandomNumber);

	CombatableEnemy->GetCombatComponent()->BeAssassinated(RandomNumber);
}

void USSGameplayAbility_Assassination::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGameplayAbility_Assassination::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Assassination::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::AbilityEventReceived(EventTag, Payload);
}
