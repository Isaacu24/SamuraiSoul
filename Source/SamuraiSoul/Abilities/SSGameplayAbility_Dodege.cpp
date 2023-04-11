// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Dodege.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../SSSamuraiCharacter.h"

USSGameplayAbility_Dodege::USSGameplayAbility_Dodege()
{
	AbilityID = ESSAbilityID::Dodge;
	AbilityInputID = ESSAbilityInputID::Dodge;

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Dodge")));

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.Jump")));
}

void USSGameplayAbility_Dodege::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	// Multyplay Debuging
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputPressed: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputReleased: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(ActorInfo->OwnerActor);

	if (nullptr != Character)
	{
		Character->Dodge();
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ActivateAbility: %s"), *GetName()));

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

void USSGameplayAbility_Dodege::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_Dodege::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}
