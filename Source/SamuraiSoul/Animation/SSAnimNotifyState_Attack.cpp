// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAnimNotifyState_Attack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Character/SSEnemyCharacter.h"
#include "../Character/SSSamuraiCharacter.h"
#include "AbilitySystemComponent.h"
#include <Components/CapsuleComponent.h>

USSAnimNotifyState_Attack::USSAnimNotifyState_Attack()
{
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

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<FHitResult> OutHits = { FHitResult() };

	UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartVector, EndVector, 20.f, ObjectTypes, false, ActorsToIgnore.Array(), EDrawDebugTrace::ForDuration, OutHits, true, FLinearColor::Red, FLinearColor::Green, 0.5f);

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
