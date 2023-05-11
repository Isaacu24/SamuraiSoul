// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Slash.h"
#include "SSAbilityTask_PlayMontageAndWait.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/SSCharacterBase.h"
#include "DataAsset/SSComboActionData.h"

USSGameplayAbility_Slash::USSGameplayAbility_Slash()
{
	AbilityID = ESSAbilityID::Slash;
	AbilityInputID = ESSAbilityInputID::Slash;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Slash")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Slash")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
}

void USSGameplayAbility_Slash::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

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

		return;
	}
}

void USSGameplayAbility_Slash::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void USSGameplayAbility_Slash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSCharacterBase* Character = Cast<ASSCharacterBase>(ActorInfo->OwnerActor);

	if (nullptr == Character)
	{
		return;
	}

	AnimInstance = Character->GetMesh()->GetAnimInstance();

	if (true == CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (nullptr != SlashMontage)
		{
			USSAbilityTask_PlayMontageAndWait* Task 
				= USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(this, NAME_None, SlashMontage, FGameplayTagContainer(), 1.f, NAME_None, false);

			Task->OnCompleted.AddDynamic(this, &ThisClass::AbilityCompleted);
			Task->OnBlendOut.AddDynamic(this, &ThisClass::AbilityBlendOut);
			Task->OnInterrupted.AddDynamic(this, &ThisClass::AbilityInterrupted);
			Task->OnCancelled.AddDynamic(this, &ThisClass::AbilityCancelled);
			Task->EventReceived.AddDynamic(this, &ThisClass::AbilityEventReceived);

			Task->ReadyForActivation();
		}
	}
}

void USSGameplayAbility_Slash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//ensure(CurrentCombo != 0);
	CurrentCombo = 0;
}

void USSGameplayAbility_Slash::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
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
	float ComboEffectiveTime = (SlashComboData->EffectiveFrameCount[ComboIndex] / SlashComboData->FrameRate) / AttackSpeedRate;
	
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
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, SlashComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *SlashComboData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, SlashMontage);	

		SetComboCheckTimer();
		HasNextComboCommand = false;		 
	}
}
