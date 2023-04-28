// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAnimNotifyState_Attack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Character/SSEnemyCharacter.h"
#include "../Character/SSSamuraiCharacter.h"
#include "AbilitySystemComponent.h"
#include <Components/CapsuleComponent.h>

USSAnimNotifyState_Attack::USSAnimNotifyState_Attack()
{
	bIsPlayer = false;
}

void USSAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(MeshComp->GetOwner());

	if (nullptr != Character)
	{
		bIsPlayer = true;
		Character->SetIsAttack(true);
	}

	else
	{
		bIsPlayer = false;
	}

}

void USSAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	FVector StartVector = MeshComp->GetSocketLocation(TEXT("Weapon_rSocket"));
	FVector EndVector = MeshComp->GetSocketLocation(TEXT("Weapon_rSocket_0"));
	
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(MeshComp->GetOwner());

	if (nullptr == Character)
	{
		return;
	}

	float AttackRadius = 10.0f;

	TArray<struct FHitResult> OutHits = { FHitResult() };
	FCollisionQueryParams Params(NAME_None, false, MeshComp->GetOwner());

	bool bResult = MeshComp->GetWorld()->SweepMultiByChannel(
		OutHits,
		StartVector,
		EndVector,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(150.0f),
		Params);

	DrawDebugSphere(MeshComp->GetWorld(), StartVector, AttackRadius, 12, FColor::Red, false, 2.0f);
	DrawDebugSphere(MeshComp->GetWorld(), EndVector, AttackRadius, 12, FColor::Red, false, 2.0f);

	for (FHitResult Result : OutHits)
	{
		if (nullptr != Result.GetActor())
		{
			if (true == bIsPlayer)
			{
				ASSEnemyCharacter* Enemy = Cast<ASSEnemyCharacter>(Result.GetActor());

				if (nullptr != Enemy
					&& nullptr == ActorsToIgnore.Find(Enemy))
				{
					Enemy->DamageCheck();
					ActorsToIgnore.Add(Enemy);
				}
			}

			else
			{
				ASSSamuraiCharacter* Player = Cast<ASSSamuraiCharacter>(Result.GetActor());

				if (nullptr != Player
					&& nullptr == ActorsToIgnore.Find(Player))
				{
					//Player->DamageCheck();
					ActorsToIgnore.Add(Player);
				}
			}
		}
	}

	//UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartVector, EndVector, 20.f, ObjectTypes, false, ActorsToIgnore.Array(), EDrawDebugTrace::ForDuration, OutHits, true, FLinearColor::Red, FLinearColor::Green, 0.5f);
}

void USSAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ActorsToIgnore.Empty();

	ASSCharacterBase* Character = Cast<ASSCharacterBase>(MeshComp->GetOwner());

	if (nullptr != Character)
	{
		Character->SetIsAttack(false);
	}
}
