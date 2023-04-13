// Fill out your copyright notice in the Description page of Project Settings.

#include "SSAnimNotifyState.h"
#include "Kismet/KismetSystemLibrary.h"

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
	TArray<AActor*> ActorsToIgnore = { nullptr };
	TArray<FHitResult> OutHits = { FHitResult() };

	UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartVector, EndVector, 20.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHits, true);
}