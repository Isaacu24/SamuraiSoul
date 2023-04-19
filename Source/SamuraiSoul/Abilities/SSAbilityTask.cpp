// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAbilityTask.h"

USSAbilityTask::USSAbilityTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USSAbilityTask::Activate()
{
	Super::Activate();
}

void USSAbilityTask::ExternalCancel()
{
	Super::ExternalCancel();
}

FString USSAbilityTask::GetDebugString() const
{
	Super::GetDebugString();
	return FString();
}

void USSAbilityTask::OnDestroy(bool AbilityEnded)
{
	Super::OnDestroy(AbilityEnded);
}
