// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Item/Weapon/SSWeapon_Katana.h"
#include "Item/Weapon/SSWeapon_DefenseBarrier.h"
#include "Character/SSCharacterBase.h"
#include <Components/CapsuleComponent.h>

// Sets default values for this component's properties
USSCombatComponent::USSCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> EXECUTION_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Execution.AM_Execution'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> EXECUTED_MONTAGE(TEXT("/Script/Engine.AnimMontage'/Game/MyContent/Animation/Character/AM_Executed.AM_Executed'"));

	if (true == EXECUTION_MONTAGE.Succeeded())
	{
		ExecutionMontage = EXECUTION_MONTAGE.Object;
	}

	if (true == EXECUTED_MONTAGE.Succeeded())
	{
		ExecutedMontage = EXECUTED_MONTAGE.Object;
	}

}

// Called when the game starts
void USSCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	ExecutionEvent.BindUObject(this, &USSCombatComponent::OnExecutionEvent);
	ExecutedEvent.BindUObject(this, &USSCombatComponent::OnExecutedEvent);
}

// Called every frame
void USSCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USSCombatComponent::EquipWeapon(USceneComponent* InParent, FName InSocketName)
{
	Weapon = GetWorld()->SpawnActor<ASSWeapon_Katana>();

	if (nullptr != Weapon)
	{
		Weapon->Equip(InParent, InSocketName);
		Weapon->SetOwner(GetOwner());
	}
}

void USSCombatComponent::EquipDefenseBarrier()
{
	DefenseBarrier = GetWorld()->SpawnActor<ASSWeapon_DefenseBarrier>();

	if (nullptr != Weapon)
	{
		DefenseBarrier->SetOwner(GetOwner());
	}

	//Barrier Off
	DefenseBarrier->SetActorHiddenInGame(true);
	DefenseBarrier->SetActorEnableCollision(false);
	DefenseBarrier->SetActorTickEnabled(false);
}

void USSCombatComponent::OnExecutionEvent()
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr != Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if(nullptr != AnimInstance)
		{
			AnimInstance->Montage_Play(ExecutionMontage);
		}
	}
}

void USSCombatComponent::OnExecutedEvent()
{
	ASSCharacterBase* Character = Cast<ASSCharacterBase>(GetOwner());

	if (nullptr != Character)
	{
		Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Executed"));
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (nullptr != AnimInstance)
		{
			AnimInstance->Montage_Play(ExecutedMontage);
		}
	}
}


