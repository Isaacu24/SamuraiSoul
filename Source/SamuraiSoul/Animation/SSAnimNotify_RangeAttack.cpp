// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SSAnimNotify_RangeAttack.h"
#include "Character/SSEnemyBossCharacter.h"

void USSAnimNotify_RangeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (nullptr != MeshComp)
	{
		ASSEnemyBossCharacter* AttackPawn = Cast<ASSEnemyBossCharacter>(MeshComp->GetOwner());

		if (nullptr != AttackPawn)
		{
			AttackPawn->RangeAttack();
		}
	}
}
