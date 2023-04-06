// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSamuraiCharacter.h"

#include "SamuraiSoul.h"

#include "SSSamuraiAnimInstance.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "SSAttributeSet.h"
#include "SSGameplayAbility.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "SSAbilitySystemComponent.h"

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
		//InputActions = CreateDefaultSubobject<USSInputConfigData>(TEXT("InputAction"));
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
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
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

		//AbilityInputAction
		//EnhancedInputComponent->BindAction(InputActions->FindAbilityInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.Jump"))),
		//	ETriggerEvent::Triggered, AbilitySystemComponent, &UAbilitySystemComponent::AbilityLocalInputPressed, static_cast<int32>(ESSAbilityInputID::Jump));
	}

	if (nullptr != AbilitySystemComponent
		&& nullptr != InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ESSAbilityInputID",
			static_cast<int32>(ESSAbilityInputID::Confirm), static_cast<int32>(ESSAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
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

	//AbilitySystemComponent->InitAbilityActorInfo(this, this);
	//InitializeAttributes();

	//if (nullptr != AbilitySystemComponent 
	//	&& nullptr != InputComponent)
	//{
	//	const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ESSAbilityInputID",
	//		static_cast<int32>(ESSAbilityInputID::Confirm), static_cast<int32>(ESSAbilityInputID::Cancel));
	//	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	//}
}

void ASSSamuraiCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASSSamuraiCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASSSamuraiCharacter::Equip()
{
	bIsEquip = !bIsEquip;

	if (true == bIsEquip)
	{
		if (0.1f < GetVelocity().Size())
		{
			MEquipDelegate.Execute();
		}

		else
		{
			MEquipRootDelegate.Execute();
		}
	}

	else
	{
		if (0.1f < GetVelocity().Size())
		{
			MUnarmDelegate.Execute();
		}

		else
		{
			MUnarmRootDelegate.Execute();
		}
	}

}

void ASSSamuraiCharacter::Dodge()
{
	if (false == bIsEquip)
	{
		return;
	}

	MDodgeDelegate.Execute();
}

void ASSSamuraiCharacter::Slash()
{
	MSlashDelegate.Execute();
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

