// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Slash.h"
#include <GameFramework/Character.h>
#include "Abilities/GameplayAbilityTypes.h"
#include "DataAsset/SSComboActionData.h"
#include "Component/SSCombatComponent.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Interface/SSCombatableInterface.h"
#include "Interface/SSBehaviorInterface.h"
#include "SSGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"


USSGameplayAbility_Slash::USSGameplayAbility_Slash()
{
	AbilityID = ESSAbilityID::Slash;

	AbilityTags.AddTag(FSSGameplayTags::Get().Ability_SlashTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_SlashTag);
	CancelAbilitiesWithTag.AddTag(FSSGameplayTags::Get().Ability_DefenseTag);
}

void USSGameplayAbility_Slash::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	if (nullptr == MyCharacter)
	{
		MyCharacter = Cast<ACharacter>(ActorInfo->OwnerActor);
	}

	if (0 == CurrentCombo)
	{
		CurrentCombo = 1;
		ComboTimerHandle.Invalidate();
		SetComboCheckTimer();
	}

	else
	{
		if (false == ComboTimerHandle.IsValid())
		{
			HasNextComboCommand = false;
		}

		else
		{
			HasNextComboCommand = true;
		}
	}
}

void USSGameplayAbility_Slash::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Slash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (nullptr == MyCharacter)
	{
		MyCharacter = Cast<ACharacter>(ActorInfo->OwnerActor);
	}

	AnimInstance = MyCharacter->GetMesh()->GetAnimInstance();

	ISSCombatableInterface* CombatablePawn = Cast<ISSCombatableInterface>(MyCharacter);

	if (true == CombatablePawn->GetCanEnemyAssassination())
	{
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(MyCharacter);

	if (nullptr != BehaviorPawn)
	{
		if (false == BehaviorPawn->IsEquip())
		{
			Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
	}

	//UAbilityTask_WaitInputPress* InputTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	//InputTask->OnPress.AddDynamic(this, &USSGameplayAbility_Slash::OnInputPressed);
	//InputTask->ReadyForActivation();

	PlayMontage(SlashMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(MyCharacter);

	if (nullptr != AIPawn)
	{
		FName NextSection = *FString::Printf(TEXT("%s%d"), *SlashComboData->MontageSectionNamePrefix, AIPawn->GetCurrentCombo());
		AnimInstance->Montage_JumpToSection(NextSection, SlashMontage);
	}
}

void USSGameplayAbility_Slash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AI = Cast<ISSCharacterAIInterface>(ActorInfo->OwnerActor);

	if (nullptr != AI)
	{
		AI->AttackEnd();
	}

	CurrentCombo = 0;
}

void USSGameplayAbility_Slash::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Slash::AbilityEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	//AnimNotify State Liking
}

void USSGameplayAbility_Slash::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(SlashComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime    = (SlashComboData->EffectiveFrameCount[ComboIndex] / SlashComboData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &USSGameplayAbility_Slash::ComboCheck, ComboEffectiveTime, false);
	}
}

void USSGameplayAbility_Slash::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (true == HasNextComboCommand)
	{
		CurrentCombo      = FMath::Clamp(CurrentCombo + 1, 1, SlashComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *SlashComboData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, SlashMontage);

		SetComboCheckTimer();

		HasNextComboCommand = false;
	}
}

//void USSGameplayAbility_Slash::OnInputPressed(float TimeWaited)
//{
//	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
//
//	ISSCombatableInterface* CombatablePawn = Cast<ISSCombatableInterface>(MyCharacter);
//
//	FSSGameplayTags Tags = {};
//	CombatablePawn->GetCombatComponent()->TryActivateAbility(Tags.Get().Ability_DefenseTag);
//}
