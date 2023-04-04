// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiAnimInstance.h"
#include "SSSamuraiCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>


USSSamuraiAnimInstance::USSSamuraiAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DODGE_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Dodge.AM_Dodge'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EQUIP_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Equip.AM_Equip'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> UNARM_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Unarm.AM_Unarm'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SLASH_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Slash.AM_Slash'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EQUIP_MONTAGE_ROOT(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Equip_ROOT.AM_Equip_ROOT'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> UNARM_MONTAGE_ROOT(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Player/AM_Unarm_ROOT.AM_Unarm_ROOT'"));

	if (true == DODGE_MONTAGE.Succeeded())
	{
		DodgeMontage = DODGE_MONTAGE.Object;
	}

	if (true == EQUIP_MONTAGE.Succeeded())
	{
		EquipMontage = EQUIP_MONTAGE.Object;
	}

	if (true == UNARM_MONTAGE.Succeeded())
	{
		UnarmMontage = UNARM_MONTAGE.Object;
	}

	if (true == SLASH_MONTAGE.Succeeded())
	{
		SlashMontage = SLASH_MONTAGE.Object;
	}

	if (true == EQUIP_MONTAGE_ROOT.Succeeded())
	{
		EquipRootMontage = EQUIP_MONTAGE_ROOT.Object;
	}

	if (true == UNARM_MONTAGE_ROOT.Succeeded())
	{
		UnarmRootMontage = UNARM_MONTAGE_ROOT.Object;
	}
}

void USSSamuraiAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSSamuraiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();

	if (false == IsValid(Pawn))
	{
		return;
	}

	Speed = Pawn->GetVelocity().Size();
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::SanitizeFloat(Speed));

	Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());

	ASSSamuraiCharacter* MyCharacter = Cast<ASSSamuraiCharacter>(Pawn);

	IsCrouch = MyCharacter->IsCrouch();
	IsAir = MyCharacter->GetCharacterMovement()->IsFalling();
	IsLastEquip = IsEquip;
	IsEquip = MyCharacter->IsEquip();
}


void USSSamuraiAnimInstance::AnimNotify_DodgeEnd()
{
	APawn* Pawn = TryGetPawnOwner();

	if (false == IsValid(Pawn))
	{
		return;
	}

	ASSSamuraiCharacter* MyCharacter = Cast<ASSSamuraiCharacter>(Pawn);
}

void USSSamuraiAnimInstance::PlayDodgeMontage()
{
	Montage_Play(DodgeMontage, 1.0f);
}

void USSSamuraiAnimInstance::PlayEquipMontage()
{
	Montage_Play(EquipMontage, 1.0f);
}

void USSSamuraiAnimInstance::PlayUnarmMontage()
{
	Montage_Play(UnarmMontage, 1.0f);
}

void USSSamuraiAnimInstance::PlaySlashMontage()
{
	Montage_Play(SlashMontage, 1.0f);
}

void USSSamuraiAnimInstance::PlayEquipRootMontage()
{
	Montage_Play(EquipRootMontage, 1.0f);
}

void USSSamuraiAnimInstance::PlayUnarmRootMontage()
{
	Montage_Play(UnarmRootMontage, 1.0f);
}
