// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAnimNotifyState_Defense.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/SSCharacterBase.h"
#include "Component/SSCombatComponent.h"

USSAnimNotifyState_Defense::USSAnimNotifyState_Defense()
{
}

void USSAnimNotifyState_Defense::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (nullptr == MeshComp->GetOwner())
	{
		return;
	}

	Character = Cast<ASSCharacterBase>(MeshComp->GetOwner());
	
	if (nullptr != Character)
	{
		Character->GetCombatComponent()->OnDefense();
		Character->GetCombatComponent()->ChangeDefenseState(EDefenseState::Parry);
	}
}

void USSAnimNotifyState_Defense::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//FVector OffsetVector = MeshComp->GetOwner()->GetActorForwardVector() * 30.f;

	//FVector StartVector = MeshComp->GetSocketLocation(TEXT("head")) + OffsetVector;
	//FVector EndVector = MeshComp->GetSocketLocation(TEXT("ball_r")) + OffsetVector;

	//ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);

	//TArray<FHitResult> OutHits = { FHitResult() };

	//bool bHit = UKismetSystemLibrary::BoxTraceMulti(MeshComp, StartVector, EndVector, FVector(10.f, 50.f, 10.f), MeshComp->GetOwner()->GetActorRotation(), TraceChannel, false, ActorsToIgnore.Array(), EDrawDebugTrace::ForDuration, OutHits, true, FLinearColor::Red, FLinearColor::Green, 0.5f);

	//for (FHitResult Result : OutHits)
	//{
	//	ASSEnemyCharacter* Enemy = Cast<ASSEnemyCharacter>(Result.GetActor());

	//	if (nullptr != Enemy
	//		&& nullptr == ActorsToIgnore.Find(Enemy))
	//	{
	//		Enemy->AttackFail();
	//		ActorsToIgnore.Add(Enemy);
	//	}
	//}
}

void USSAnimNotifyState_Defense::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (nullptr == MeshComp->GetOwner())
	{
		return;
	}

	Character = Cast<ASSCharacterBase>(MeshComp->GetOwner());

	if (nullptr != Character)
	{
		Character->GetCombatComponent()->ChangeDefenseState(EDefenseState::Defense);
	}
}
