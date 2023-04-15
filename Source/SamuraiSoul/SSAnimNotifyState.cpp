// Fill out your copyright notice in the Description page of Project Settings.

#include "SSAnimNotifyState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AI/SSEnemyCharacter.h"
#include "AbilitySystemComponent.h"

USSAnimNotifyState::USSAnimNotifyState()
{

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

	//다른 사람이 봐도 부담스럽다
	//직관적, 최선
	for (FHitResult Result : OutHits)
	{
		ASSEnemyCharacter* Enemy = Cast<ASSEnemyCharacter>(Result.GetActor());

		if (nullptr != Enemy
			&& nullptr == ActorsToIgnore.Find(Enemy))
		{
			Enemy->DamageCheck();
			ActorsToIgnore.Add(Enemy);
		}
	}
}

void USSAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ActorsToIgnore.Empty();
}

