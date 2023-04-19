// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiCharacter.h"

#include "SamuraiSoul.h"

#include "SSSamuraiAnimInstance.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Abilities/SSAttributeSet.h"
#include "Abilities/SSGameplayAbility.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "Abilities/SSAbilitySystemComponent.h"

#include "SSInputConfigData.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASSSamuraiCharacter::ASSSamuraiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("/Script/Engine.SkeletalMesh'/Game/GhostSamurai_Bundle/GhostSamurai/Character/Mesh/SK_GhostSamurai_katana.SK_GhostSamurai_katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Player/AB_SSSamuraiCharacter.AB_SSSamuraiCharacter_C'"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> INPUT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MyContent/Input/IMC_SamuraiCharacter.IMC_SamuraiCharacter'"));

	if (true == SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	if (INPUT_CONTEXT.Succeeded())
	{
		InputMappingContext = INPUT_CONTEXT.Object;

		//InputAction's is null! Must be Overridden in the Character Blueprint Class.
		InputActions = CreateDefaultSubobject<USSInputConfigData>(TEXT("InputActions"));
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -88.5f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	RootComponent = GetCapsuleComponent();

	Arm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(Arm);

	Arm->TargetArmLength = 500.f;
	Arm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

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
	
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (nullptr != PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (nullptr != Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void ASSSamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.CrouchStart"))),
			ETriggerEvent::Started, this, &ASSSamuraiCharacter::CrouchStart);

		EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.CrouchEnd"))),
			ETriggerEvent::Completed, this, &ASSSamuraiCharacter::CrouchEnd);

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

void ASSSamuraiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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

void ASSSamuraiCharacter::HandleRunActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Run));
}

void ASSSamuraiCharacter::HandleRunActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Run));
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

void ASSSamuraiCharacter::HandleCrouchActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Crouch));
}

void ASSSamuraiCharacter::HandleCrouchActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Crouch));
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

