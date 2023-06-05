// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/SSAnimNotifyState_Dead.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

USSAnimNotifyState_Dead::USSAnimNotifyState_Dead()
{
}

void USSAnimNotifyState_Dead::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                          const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	/*ensure(MeshComp());

	ACharacter* Character = Cast<ACharacter>(MeshComp()->GetOwner());

	ensure(Character);

	USkeletalMeshComponent* CharacterMesh = MeshComp();

	CharacterMesh->SetCollisionProfileName(FName("Ragdoll"));
	CharacterMesh->SetSimulatePhysics(true);
	CharacterMesh->WakeAllRigidBodies();

	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CharacterMesh->AddImpulse((Character->GetVelocity() / 2.f) * CharacterMesh->GetMass());
	CharacterMesh->AddRadialImpulse(Character->GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);*/
}

void USSAnimNotifyState_Dead::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                         const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void USSAnimNotifyState_Dead::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
