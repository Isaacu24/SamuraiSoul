// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAnimNotifyState_Defense.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../AI/SSEnemyCharacter.h"
#include "../Player/SSCharacterBase.h"
#include "../Player/SSSamuraiCharacter.h"
#include "AbilitySystemComponent.h"

USSAnimNotifyState_Defense::USSAnimNotifyState_Defense()
{
}

void USSAnimNotifyState_Defense::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{

}

void USSAnimNotifyState_Defense::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	FVector StartVector = MeshComp->GetSocketLocation(TEXT("head"));
	FVector EndVector = MeshComp->GetSocketLocation(TEXT("ball_r"));

	Character = Cast<ASSCharacterBase>(MeshComp->GetOwner());

	if (nullptr == Character)
	{
		return;
	}

	float AttackRange = 200.0f;
	float AttackRadius = 50.0f;

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, MeshComp->GetOwner());

	bool bResult = MeshComp->GetWorld()->SweepSingleByChannel(
		HitResult,
		StartVector,
		EndVector,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(150.0f),
		Params);

	if (true == bResult)
	{
		if (nullptr != HitResult.GetActor())
		{
			ASSEnemyCharacter* Enemy = Cast<ASSEnemyCharacter>(HitResult.GetActor());

			if (nullptr != Enemy
				&& nullptr == ActorsToIgnore.Find(Enemy))
			{
				Enemy->AttackFail();
				ActorsToIgnore.Add(Enemy);
			}
		}
	}
//
//#if ENABLE_DRAW_DEBUG
//	FVector TraceVec = StartVector * AttackRange;
//	FVector Center = MeshComp->GetOwner()->GetActorLocation() + TraceVec * 0.5f;
//	float HalfHeight = AttackRange * 0.5f + AttackRadius;
//	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
//	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
//	float DebugLifeTime = 5.0f;
//
//	DrawDebugCapsule(MeshComp->GetWorld(), Center, HalfHeight, AttackRadius, CapsuleRot, DrawColor, false, DebugLifeTime);
//#endif
}

void USSAnimNotifyState_Defense::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ActorsToIgnore.Empty();
}
