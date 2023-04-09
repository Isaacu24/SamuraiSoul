// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Jump.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SSSamuraiCharacter.h"

USSGameplayAbility_Jump::USSGameplayAbility_Jump()
{
	AbilityID = ESSAbilityID::Jump;
	AbilityInputID = ESSAbilityInputID::Jump;

	// 이렇게 태그를 지정해두면, 이후에 해당 태그를 가진 어빌리티들을 비활성할 수도 있음. ex. 마나가 없으니 마나를 사용하는 스킬은 모두 꺼라.
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.UseSP")));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.UseSP.Jump")));
}

void USSGameplayAbility_Jump::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	// 멀티플레이 환경에서 이 함수를 활용해서 디버깅 가능.
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputPressed: %s"), *GetName()));
}

void USSGameplayAbility_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("InputReleased: %s"), *GetName()));
}

void USSGameplayAbility_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(ActorInfo->OwnerActor);

	if (nullptr != Character)
	{
		Character->Jump();
	}

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ActivateAbility: %s"), *GetName()));

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

void USSGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("EndAbility: %s"), *GetName()));
}

void USSGameplayAbility_Jump::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("ApplyCost: %s"), *GetName()));
}
