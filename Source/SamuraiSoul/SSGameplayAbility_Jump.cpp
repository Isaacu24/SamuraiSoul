// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameplayAbility_Jump.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SSSamuraiCharacter.h"

USSGameplayAbility_Jump::USSGameplayAbility_Jump()
{
	AbilityID = ESSAbilityID::Jump;
	AbilityInputID = ESSAbilityInputID::Jump;

	// �̷��� �±׸� �����صθ�, ���Ŀ� �ش� �±׸� ���� �����Ƽ���� ��Ȱ���� ���� ����. ex. ������ ������ ������ ����ϴ� ��ų�� ��� ����.
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.UseSP")));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("SSAbilities.UseSP.Jump")));
}

void USSGameplayAbility_Jump::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	// ��Ƽ�÷��� ȯ�濡�� �� �Լ��� Ȱ���ؼ� ����� ����.
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
