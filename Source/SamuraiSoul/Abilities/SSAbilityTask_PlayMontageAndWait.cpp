// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAbilityTask_PlayMontageAndWait.h"
#include "SSAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimInstance.h"

USSAbilityTask_PlayMontageAndWait::USSAbilityTask_PlayMontageAndWait(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Rate                 = 1.f;
	bStopWhenAbilityEnds = true;
}

void USSAbilityTask_PlayMontageAndWait::Activate()
{
	if (nullptr == Ability)
	{
		return;
	}

	bool bPlayedMontage                                 = false;
	USSAbilitySystemComponent* SSAbilitySystemComponent = GetTargetASC();

	if (nullptr != SSAbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance                = ActorInfo->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			// Bind to event callback
			EventHandle = SSAbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTags,
			                                                                             FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this,
				                                                                             &USSAbilityTask_PlayMontageAndWait::OnGameplayEvent));

			if (SSAbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.f)
			{
				// Playing a montage could potentially fire off a callback into game code which could kill this ability! Early out if we are  pending kill.
				if (ShouldBroadcastAbilityTaskDelegates() == false)
				{
					return;
				}

				CancelledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &USSAbilityTask_PlayMontageAndWait::OnAbilityCancelled);

				BlendingOutDelegate.BindUObject(this, &USSAbilityTask_PlayMontageAndWait::OnMontageBlendingOut);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &USSAbilityTask_PlayMontageAndWait::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
				if (Character && (Character->GetLocalRole() == ROLE_Authority ||
					(Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() ==
						EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
				{
					Character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);
				}

				bPlayedMontage = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("USSAbilityTask_PlayMontageAndWaitForEvent call to PlayMontage failed!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USSAbilityTask_PlayMontageAndWaitForEvent called on invalid AbilitySystemComponent"));
	}

	if (false == bPlayedMontage)
	{
		if (true == ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

	SetWaitingOnAvatar();
}

void USSAbilityTask_PlayMontageAndWait::ExternalCancel()
{
	check(nullptr != AbilitySystemComponent);

	OnAbilityCancelled();

	Super::ExternalCancel();
}

FString USSAbilityTask_PlayMontageAndWait::GetDebugString() const
{
	UAnimMontage* PlayingMontage = nullptr;

	if (nullptr != Ability)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance                = ActorInfo->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			PlayingMontage = AnimInstance->Montage_IsActive(MontageToPlay) ? MontageToPlay : AnimInstance->GetCurrentActiveMontage();
		}
	}

	return FString::Printf(TEXT("PlayMontageAndWaitForEvent. MontageToPlay: %s  (Currently Playing): %s"), *GetNameSafe(MontageToPlay),
	                       *GetNameSafe(PlayingMontage));
}

void USSAbilityTask_PlayMontageAndWait::OnDestroy(bool AbilityEnded)
{
	if (nullptr != Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(CancelledHandle);

		if (true == AbilityEnded
			&& true == bStopWhenAbilityEnds)
		{
			StopPlayingMontage();
		}
	}

	USSAbilitySystemComponent* SSAbilitySystemComponent = GetTargetASC();
	if (nullptr != SSAbilitySystemComponent)
	{
		SSAbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

USSAbilityTask_PlayMontageAndWait* USSAbilityTask_PlayMontageAndWait::PlayMontageAndWaitForEvent(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer EventTags, float Rate, FName StartSection,
	bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	USSAbilityTask_PlayMontageAndWait* MyObj = NewAbilityTask<USSAbilityTask_PlayMontageAndWait>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay                     = MontageToPlay;
	MyObj->EventTags                         = EventTags;
	MyObj->Rate                              = Rate;
	MyObj->StartSection                      = StartSection;
	MyObj->AnimRootMotionTranslationScale    = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds              = bStopWhenAbilityEnds;

	return MyObj;
}

bool USSAbilityTask_PlayMontageAndWait::StopPlayingMontage()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();

	if (nullptr == ActorInfo)
	{
		return false;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

	if (nullptr == AnimInstance)
	{
		return false;
	}

	// Check if the montage is still playing
	// The ability would have been interrupted, in which case we should automatically stop the montage
	if (nullptr != Ability
		&& nullptr != AbilitySystemComponent)
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == Ability
			&& AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			// Unbind delegates so they don't get called as well
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}

	return false;
}

USSAbilitySystemComponent* USSAbilityTask_PlayMontageAndWait::GetTargetASC()
{
	return Cast<USSAbilitySystemComponent>(AbilitySystemComponent);
}

void USSAbilityTask_PlayMontageAndWait::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (nullptr != Ability && Ability->GetCurrentMontage() == MontageToPlay)
	{
		if (Montage == MontageToPlay)
		{
			AbilitySystemComponent->ClearAnimatingAbility(Ability);

			// Reset AnimRootMotionTranslationScale
			ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
			if (Character && (Character->GetLocalRole() == ROLE_Authority ||
				(Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
			{
				Character->SetAnimRootMotionTranslationScale(1.f);
			}
		}
	}

	if (true == bInterrupted)
	{
		if (true == ShouldBroadcastAbilityTaskDelegates())
		{
			OnInterrupted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

	else
	{
		if (true == ShouldBroadcastAbilityTaskDelegates())
		{
			OnBlendOut.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void USSAbilityTask_PlayMontageAndWait::OnAbilityCancelled()
{
	if (true == StopPlayingMontage())
	{
		// Let the BP handle the interrupt as well
		if (true == ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void USSAbilityTask_PlayMontageAndWait::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (true == ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

	EndTask();
}

void USSAbilityTask_PlayMontageAndWait::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (true == ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag           = EventTag;

		EventReceived.Broadcast(EventTag, TempData);
	}
}
