// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiCharacter.h"

#include "Game/SamuraiSoul.h"

#include "Animation/SSSamuraiAnimInstance.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Abilities/SSAttributeSet.h"
#include "Abilities/SSGameplayAbility.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "Abilities/SSAbilitySystemComponent.h"

#include "Input/SSInputConfigData.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Components/InputComponent.h>

#include "Component/SSCombatComponent.h"
#include "SSCharacterControlData.h"

// Sets default values
ASSSamuraiCharacter::ASSSamuraiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("/Script/Engine.SkeletalMesh'/Game/GhostSamurai_Bundle/GhostSamurai/Character/Mesh/SK_GhostSamurai_katana.SK_GhostSamurai_katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/Player/AB_SSSamuraiCharacter.AB_SSSamuraiCharacter_C'"));

	if (true == SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -89.f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	CameraArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	
	FVector SpringArmLocation = CameraArm->GetRelativeLocation();
	SpringArmLocation.Z += 15.f; 
	CameraArm->SetRelativeLocation(SpringArmLocation);

	JumpMaxCount = 1;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	InputActions = CreateDefaultSubobject<USSInputConfigData>(TEXT("InputActions"));

	ControlType = ECharacterControlType::Keyboard;
}

// Called when the game starts or when spawned
void ASSSamuraiCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterControl(ControlType);
}

void ASSSamuraiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CombatComponent->EquipWeapon(GetMesh(), FName("Weapon_rSocket"));
	CombatComponent->EquipDefenseBarrier();
	CombatComponent->AttackEvent.BindUObject(this, &ASSSamuraiCharacter::AttackEvent);
}

void ASSSamuraiCharacter::SetCharacterControlData(const USSCharacterControlData* ControlData)
{
	Super::SetCharacterControlData(ControlData);

	CameraArm->TargetArmLength = ControlData->TargetArmLength;
	CameraArm->SetRelativeRotation(ControlData->RelativeRotaion);
	CameraArm->bUsePawnControlRotation = ControlData->bUsePawnControlRotation;
	CameraArm->bInheritPitch = ControlData->bInheritPitch;
	CameraArm->bInheritYaw = ControlData->bInheritYaw;
	CameraArm->bInheritRoll = ControlData->bInheritRoll;
	CameraArm->bDoCollisionTest = ControlData->bDoCollisionTest;
}

// Called every frame
void ASSSamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_All, nullptr);
	}
}

// Called to bind functionality to input
void ASSSamuraiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//NativeinputAction
		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Move"))),
			ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::Move);

		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Look"))),
			ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::Look);

		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Run"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::Run);

		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.UnRun"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::UnRun);

		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.CrouchStart"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::CrouchStart);

		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.CrouchEnd"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::CrouchEnd);
		
		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.ChangeControl"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::ChangeCharacterControl);

		//AbilityInputAction
		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Jump"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::HandleJumpActionPressed);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Jump"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::HandleJumpActionReleased);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Dodge"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::HandleDodgeActionPressed);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Dodge"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::HandleDodgeActionReleased);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.EquipAndUnarm"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::HandleEquipAndUnarmActionPressed);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.EquipAndUnarm"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::HandleEquipAndUnarmActionReleased);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Slash"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::HandleSlashActionPressed);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Slash"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::HandleSlashActionReleased);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Defense"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::HandleDefenseActionPressed);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Defense"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::HandleDefenseActionReleased);
	}
}

void ASSSamuraiCharacter::OnRep_PlayerState()
{
	//Replication no idea
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
}

void ASSSamuraiCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASSSamuraiCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASSSamuraiCharacter::Run()
{
	if (true == bIsCrouch)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ASSSamuraiCharacter::UnRun()
{
	if (true == bIsCrouch)
	{
		return;
	}

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

void ASSSamuraiCharacter::ChangeCharacterControl()
{
	switch (ControlType)
	{
	case ECharacterControlType::Keyboard:
		SetCharacterControl(ECharacterControlType::Gamepad);
		break;
	case ECharacterControlType::Gamepad:
		SetCharacterControl(ECharacterControlType::Keyboard);
		break;
	default:
		break;
	}
}

void ASSSamuraiCharacter::SetCharacterControl(ECharacterControlType CharacterControlType)
{
	USSCharacterControlData* NewCharacterControl = CharacterControlMap[CharacterControlType];
	check(NewCharacterControl);

	SetCharacterControlData(NewCharacterControl);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (nullptr != PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (nullptr != Subsystem)
		{
			Subsystem->ClearAllMappings();
			UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;

			if (nullptr != NewMappingContext)
			{
				Subsystem->AddMappingContext(NewMappingContext, 0);
			}
		}
	}

	ControlType = CharacterControlType;
}

void ASSSamuraiCharacter::AttackEvent(EWeaponType Type)
{

}

void ASSSamuraiCharacter::HitEvent(EWeaponType Type)
{
}

void ASSSamuraiCharacter::HandleDodgeActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Dodge));
}

void ASSSamuraiCharacter::HandleDodgeActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Dodge));
}

void ASSSamuraiCharacter::HandleEquipAndUnarmActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::EquipUnarm));
}

void ASSSamuraiCharacter::HandleEquipAndUnarmActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::EquipUnarm));
}

void ASSSamuraiCharacter::HandleJumpActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Jump));
}

void ASSSamuraiCharacter::HandleJumpActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Jump));
}

void ASSSamuraiCharacter::HandleSlashActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Slash));
}

void ASSSamuraiCharacter::HandleSlashActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Slash));
}

void ASSSamuraiCharacter::HandleDefenseActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Defense));
}

void ASSSamuraiCharacter::HandleDefenseActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Defense));
}

