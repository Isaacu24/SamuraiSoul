// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/SSGameplayAbility.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Abilities/SSAttributeSet.h"
#include "Game/SamuraiSoul.h"
#include "SSCharacterControlData.h"

// Sets default values
ASSCharacterBase::ASSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USSAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<USSAttributeSet>(TEXT("Attributes"));

	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("SSCharacter"));
	//GetMesh()->SetCollisionProfileName("CharacterMesh");

	static ConstructorHelpers::FObjectFinder<USSCharacterControlData> KEYBOARDCONTROLDATA(TEXT("/Script/SamuraiSoul.SSCharacterControlData'/Game/MyContent/CharacterControl/ABC_Keyboard.ABC_Keyboard'"));

	if (nullptr != KEYBOARDCONTROLDATA.Object)
	{
		CharacterControlMap.Add({ ECharacterControlType::Keyboard, KEYBOARDCONTROLDATA.Object });
	}

	static ConstructorHelpers::FObjectFinder<USSCharacterControlData> QUATERCONTROLDATA(TEXT("/Script/SamuraiSoul.SSCharacterControlData'/Game/MyContent/CharacterControl/ABC_Gamepad.ABC_Gamepad'"));

	if (nullptr != QUATERCONTROLDATA.Object)
	{
		CharacterControlMap.Add({ ECharacterControlType::Gamepad, QUATERCONTROLDATA.Object });
	}

}

UAbilitySystemComponent* ASSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
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

// Called every frame
void ASSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASSCharacterBase::DamageCheck()
{
	//if (0.f >= Attributes->GetHealth())
	//{
	//	return;
	//}

	//if (nullptr != AbilitySystemComponent
	//	&& nullptr != DamageEffect)
	//{
	//	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	//	EffectContext.AddSourceObject(this);

	//	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1, EffectContext);

	//	if (SpecHandle.IsValid())
	//	{
	//		FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	//		UE_LOG(LogTemp, Log, TEXT("Enemy HP: %f"), Attributes->GetHealth());

	//		//Hit Ability
	//		HitDelegate.Execute();

	//		if (0.f >= Attributes->GetHealth())
	//		{
	//			DeathDelegate.Execute();

	//			//USkeletalMeshComponent* MyMesh = GetMesh();

	//			//if (!MyMesh)
	//			//	return;

	//			//MyMesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));

	//			//MyMesh->SetSimulatePhysics(true);
	//			//MyMesh->WakeAllRigidBodies();

	//			//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//			////SetMovementMode(EMovementMode::MOVE_None);

	//			//MyMesh->AddImpulse((GetVelocity() / 2.f)* MyMesh->GetMass());
	//			//MyMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
	//		}
	//	}
	//}
}

void ASSCharacterBase::AttackFail()
{
	//AttackFailDelegate.Execute();
}

