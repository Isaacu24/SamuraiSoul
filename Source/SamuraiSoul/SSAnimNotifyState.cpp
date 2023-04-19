// Fill out your copyright notice in the Description page of Project Settings.

#include "SSAnimNotifyState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AI/SSEnemyCharacter.h"
#include "SSSamuraiCharacter.h"
#include "AbilitySystemComponent.h"

USSAnimNotifyState::USSAnimNotifyState()
{

}


void USSAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ASSSamuraiCharacter* Character = Cast<ASSSamuraiCharacter>(MeshComp->GetOwner());
	
	if (nullptr != Character)
	{
		bIsPlayer = true;
	}
	
	else
	{
		bIsPlayer = false;
	}
}

void USSAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	FVector StartVector = MeshComp->GetSocketLocation(TEXT("Weapon_rSocket"));
	FVector EndVector = MeshComp->GetSocketLocation(TEXT("Weapon_rSocket_0"));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<FHitResult> OutHits = { FHitResult() };

	UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartVector, EndVector, 20.f, ObjectTypes, false, ActorsToIgnore.Array(), EDrawDebugTrace::ForDuration, OutHits, true);

	for (FHitResult Result : OutHits)
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

void USSAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ActorsToIgnore.Empty();
}

