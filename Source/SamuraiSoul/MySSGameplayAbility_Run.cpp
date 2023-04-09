// Fill out your copyright notice in the Description page of Project Settings.


#include "MySSGameplayAbility_Run.h"

UMySSGameplayAbility_Run::UMySSGameplayAbility_Run()
{
	AbilityID = ESSAbilityID::Run;
	AbilityInputID = ESSAbilityInputID::Run;

	//AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.UseSP")));
	//AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.UseSP.Jump")));
}

void UMySSGameplayAbility_Run::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UMySSGameplayAbility_Run::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

void UMySSGameplayAbility_Run::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMySSGameplayAbility_Run::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMySSGameplayAbility_Run::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}