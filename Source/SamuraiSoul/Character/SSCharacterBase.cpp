// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/SSGameplayAbility.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Abilities/SSAttributeSet.h"
#include "Game/SamuraiSoul.h"
#include "SSCharacterControlData.h"
#include "MotionWarpingComponent.h"
#include "Component/SSCombatComponent.h"

ASSCharacterBase::ASSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USSAbilitySystemComponent>(TEXT("AbilitySystem Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<USSAttributeSet>(TEXT("Attributes"));

	CombatComponent = CreateDefaultSubobject<USSCombatComponent>("Combat Component");
	MotionWarpComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping Component"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("SSCapsule"));
	GetMesh()->SetCollisionProfileName("NoCollision");
}

void ASSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASSCharacterBase::SetCharacterControlData(const USSCharacterControlData* ControlData)
{
	//Pawn
	bUseControllerRotationYaw = ControlData->bUseControllerRotationYaw;

	// CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = ControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = ControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = ControlData->RotationRate;
}

void ASSCharacterBase::InitializeAttributes()
{
	if (nullptr != AbilitySystemComponent
		&& nullptr != DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ASSCharacterBase::GiveAbilities()
{
	if (true == HasAuthority()
		&& nullptr != AbilitySystemComponent)
	{
		for (TSubclassOf<USSGameplayAbility>& StartUpAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(StartUpAbility, 1, static_cast<int32>(StartUpAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void ASSCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Server Gas Init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
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

void ASSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
