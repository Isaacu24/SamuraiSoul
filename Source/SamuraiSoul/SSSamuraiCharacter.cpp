// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiCharacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "SSSamuraiAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "SSGameplayAbility.h"
#include "SSAttributeSet.h"
#include "SamuraiSoul.h"
#include <GameplayEffectTypes.h>

// Sets default values
ASSSamuraiCharacter::ASSSamuraiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/GhostSamurai_Bundle/GhostSamurai/Character/Mesh/SK_GhostSamurai_katana.SK_GhostSamurai_katana'"));

	if (true == BodyMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BodyMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Player/AB_SSSamuraiCharacter.AB_SSSamuraiCharacter_C'"));

	if (true == CharacterAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnim.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -87.5f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	RootComponent = GetCapsuleComponent();

	Arm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(Arm);

	Arm->TargetArmLength = 500.f;
	Arm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<USSAttributeSet>(TEXT("Attributes"));

	JumpMaxCount = 1;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("SSSamuraiCharacter"));

	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ControlRotation(Controller) -> SpringArm
	Arm->bUsePawnControlRotation = true;

	// Controller -> SpringArm
	Arm->bInheritPitch = true;
	Arm->bInheritYaw = true;
	Arm->bInheritRoll = false;

	// Movement Component -> Pawn
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
}

// Called when the game starts or when spawned
void ASSSamuraiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSSamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("Character is Die :: %s"), bIsEquip ? TEXT("true") : TEXT("false"));
}

// Called to bind functionality to input
void ASSSamuraiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("FowardBackMove", this, &ASSSamuraiCharacter::FowardBackMove);
	PlayerInputComponent->BindAxis("RightLeftMove", this, &ASSSamuraiCharacter::RightLeftMove);

	PlayerInputComponent->BindAxis("LookUp", this, &ASSSamuraiCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASSSamuraiCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASSSamuraiCharacter::Jump);

	PlayerInputComponent->BindAction("Equip", EInputEvent::IE_Pressed, this, &ASSSamuraiCharacter::Equip);
	PlayerInputComponent->BindAction("Dodge", EInputEvent::IE_Pressed, this, &ASSSamuraiCharacter::Dodge);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ASSSamuraiCharacter::Run);
	PlayerInputComponent->BindAction("UnRun", EInputEvent::IE_Released, this, &ASSSamuraiCharacter::UnRun);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ASSSamuraiCharacter::CrouchStart);
	PlayerInputComponent->BindAction("UnCrouch", EInputEvent::IE_Released, this, &ASSSamuraiCharacter::CrouchEnd);

	if (nullptr != AbilitySystemComponent
		&& nullptr != InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ESSAbilityInputID",
			static_cast<int32>(ESSAbilityInputID::Confirm), static_cast<int32>(ESSAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

UAbilitySystemComponent* ASSSamuraiCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASSSamuraiCharacter::InitializeAttributes()
{
	//1
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

void ASSSamuraiCharacter::GiveAbilities()
{
	//2
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

void ASSSamuraiCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Server Gas Init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void ASSSamuraiCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();

	if (nullptr != AbilitySystemComponent 
		&& nullptr != InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ESSAbilityInputID",
			static_cast<int32>(ESSAbilityInputID::Confirm), static_cast<int32>(ESSAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ASSSamuraiCharacter::FowardBackMove(float Value)
{
	AddMovementInput(FRotationMatrix(FRotator(0.f, GetController()->GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X), Value);
}

void ASSSamuraiCharacter::RightLeftMove(float Value)
{
	AddMovementInput(FRotationMatrix(FRotator(0.f, GetController()->GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), Value);
}

void ASSSamuraiCharacter::Equip()
{
	bIsEquip = !bIsEquip;

	USSSamuraiAnimInstance* AnimInstance = Cast<USSSamuraiAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr == AnimInstance)
	{
		return;
	}

	if (true == bIsEquip)
	{
		if (0.1f < GetVelocity().Size())
		{
			AnimInstance->PlayEquipMontage();
		}

		else
		{
			AnimInstance->PlayEquipRootMontage();
		}
	}

	else
	{
		if (0.1f < GetVelocity().Size())
		{
			AnimInstance->PlayUnarmMontage();
		}

		else
		{
			AnimInstance->PlayUnarmRootMontage();
		}
	}

}

void ASSSamuraiCharacter::Dodge()
{
	if (false == bIsEquip)
	{
		return;
	}

	USSSamuraiAnimInstance* AnimInstance = Cast<USSSamuraiAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr == AnimInstance)
	{
		return;
	}

	AnimInstance->PlayDodgeMontage();
}

void ASSSamuraiCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ASSSamuraiCharacter::UnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void ASSSamuraiCharacter::CrouchStart()
{
	bIsCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

void ASSSamuraiCharacter::CrouchEnd()
{
	bIsCrouch = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;

}

