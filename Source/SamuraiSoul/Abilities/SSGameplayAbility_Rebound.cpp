// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGameplayAbility_Rebound.h"
#include "Interface/SSCharacterAIInterface.h"
#include "SSGameplayTags.h"

USSGameplayAbility_Rebound::USSGameplayAbility_Rebound()
{
	AbilityID      = ESSAbilityID::Rebound;
	AbilityInputID = ESSAbilityInputID::None;

	AbilityTags.AddTag(FSSGameplayTags::Get().ReboundTag);
	ActivationOwnedTags.AddTag(FSSGameplayTags::Get().ReboundTag);
	ActivationBlockedTags.AddTag(FSSGameplayTags::Get().ReactionTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag    = FSSGameplayTags::Get().ReboundTag;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Emplace(TriggerData);
}

void USSGameplayAbility_Rebound::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayMontage(ReboundMontage, Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USSGameplayAbility_Rebound::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ActorInfo->AvatarActor);

	if (nullptr != AIPawn)
	{
		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([AIPawn]
		{
			AIPawn->SetRebound(false);
		});

		GetWorld()->GetTimerManager().SetTimer(ReboundEndTimer, TimerCallback, 1.0f, false);
	}
}

void USSGameplayAbility_Rebound::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}
