// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SSAnimNotify_CameraShake.h"
#include "Kismet/GameplayStatics.h"

void USSAnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	APawn* ControllerPawn = Cast<APawn>(MeshComp->GetOwner());

	if (nullptr != ControllerPawn)
	{
		UGameplayStatics::PlayWorldCameraShake(ControllerPawn->GetController(), CameraShakeClass, ControllerPawn->GetActorLocation(), 3000.0f, 1.0f);;
	}
}
