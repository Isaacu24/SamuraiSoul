// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/SSGameplayAbility.h"
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

	const USSAttributeSet* Attribute = AbilitySystemComponent->GetSet<USSAttributeSet>();

	//float a = Attribute->GetMaxHealth();

	StatComponent->InitializeAbilityDelegates();

	//InitializeAttributes();
	//GiveAbilities();
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

void ASSCharacterBase::InitializeAttributes()
{
	//if (nullptr != AbilitySystemComponent
	//	&& nullptr != DefaultAttributeEffect)
	//{
	//	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	//	EffectContext.AddSourceObject(this);

	//	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

	//	if (SpecHandle.IsValid())
	//	{
	//		FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	//	}
	//}
}

void ASSCharacterBase::GiveAbilities()
{
	//if (true == HasAuthority()
	//	&& nullptr != AbilitySystemComponent)
	//{
	//	for (TSubclassOf<USSGameplayAbility>& StartUpAbility : DefaultAbilities)
	//	{
	//		AbilitySystemComponent->GiveAbility(
	//		                                    FGameplayAbilitySpec(StartUpAbility, 1, static_cast<int32>(StartUpAbility.GetDefaultObject()->AbilityInputID),
	//		                                                         this));
	//	}
	//}
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

void ASSCharacterBase::Die() const
{
	USkeletalMeshComponent* MyMesh = GetMesh();

	if (!MyMesh)
	{
		return;
	}

	MyMesh->SetCollisionProfileName(FName("Ragdoll"));

	MyMesh->SetSimulatePhysics(true);
	MyMesh->WakeAllRigidBodies();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MyMesh->AddImpulse((GetVelocity() / 2.f) * MyMesh->GetMass());
	MyMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);

	if (true == OnCharacterEnded.IsBound())
	{
		OnCharacterEnded.Broadcast();
	}
}

UAbilitySystemComponent* ASSCharacterBase::GetAbilitySystemComponent() const
{
	return GetSSAbilitySystemComponent();
}

void ASSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
