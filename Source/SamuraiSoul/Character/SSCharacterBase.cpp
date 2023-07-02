// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterBase.h"
#include "AbilitySystemComponent.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Abilities/SSAttributeSet.h"
#include "SSCharacterControlData.h"
#include "MotionWarpingComponent.h"
#include "Component/SSCharacterStatComponent.h"
#include "UI/SSHPBarWidget.h"
#include "SSGameplayTags.h"
#include "DataAsset/SSAbilitySet.h"
#include "DataAsset/SSCharacterData.h"

ASSCharacterBase::ASSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USSAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	StatComponent = CreateDefaultSubobject<USSCharacterStatComponent>(TEXT("SSCharacterStat Component"));

	MotionWarpComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping Component"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("SSCapsule"));
	GetMesh()->SetCollisionProfileName("NoCollision");
}

void ASSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASSCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASSCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Server Gas Init
	check(nullptr != AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->SetTagMapCount(FSSGameplayTags::Get().DeadTag, 0);

	check(nullptr != CharacterData);
	check(nullptr != CharacterData->AbilitySet);
	CharacterData->AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &AbilitySetHandles);

	StatComponent->SetAbilityDelegates();
}

void ASSCharacterBase::SetCharacterControlData(const USSCharacterControlData* ControlData)
{
	//Pawn
	bUseControllerRotationYaw = ControlData->bUseControllerRotationYaw;

	// CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement     = ControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = ControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate                  = ControlData->RotationRate;
}

void ASSCharacterBase::SetupCharacterWidget(USSUserWidget* InUserWidget)
{
}

void ASSCharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (nullptr != AbilitySystemComponent)
	{
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void ASSCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ASSCharacterBase::Die()
{
	if (nullptr != Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	OnCharacterDead.Broadcast();
}

const FVector2D& ASSCharacterBase::GetMovementVector() const
{
	return FVector2D::ZeroVector;
}

UAbilitySystemComponent* ASSCharacterBase::GetAbilitySystemComponent() const
{
	return GetSSAbilitySystemComponent();
}

const bool ASSCharacterBase::GetAxisInput() const
{
	return bIsAixsInput;
}

void ASSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
