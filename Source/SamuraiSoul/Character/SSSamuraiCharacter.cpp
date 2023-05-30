// Fill out your copyright notice in the Description page of Project Settings.
#include "SSSamuraiCharacter.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include <Math/UnrealMathUtility.h>

#include "Input/SSInputConfigData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Components/InputComponent.h>
#include "Interface/SSCharacterAIInterface.h"

#include "Abilities/SSAbilitySystemComponent.h"
#include "Component/SSCombatComponent.h"
#include "SSCharacterControlData.h"
#include "Component/SSCharacterStatComponent.h"
#include "UI/SSHUDWidget.h"

// Sets default values
ASSSamuraiCharacter::ASSSamuraiCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_BODY(TEXT("/Script/Engine.SkeletalMesh'/Game/GhostSamurai_Bundle/GhostSamurai/Character/Mesh/SK_GhostSamurai_katana.SK_GhostSamurai_katana'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/Player/AB_SSSamuraiCharacter.AB_SSSamuraiCharacter_C'"));

	static ConstructorHelpers::FObjectFinder<USSCharacterControlData>
		KEYBOARD_CONTROLDATA(TEXT("/Script/SamuraiSoul.SSCharacterControlData'/Game/MyContent/DataAsset/Character/Control/DA_Keyboard.DA_Keyboard'"));

	static ConstructorHelpers::FObjectFinder<USSCharacterControlData>
		GAMEPAD_CONTROLDATA(TEXT("/Script/SamuraiSoul.SSCharacterControlData'/Game/MyContent/DataAsset/Character/Control/DA_Gamepad.DA_Gamepad'"));

	if (true == SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	if (nullptr != KEYBOARD_CONTROLDATA.Object)
	{
		CharacterControlMap.Add({ECharacterControlType::Keyboard, KEYBOARD_CONTROLDATA.Object});
	}

	if (nullptr != GAMEPAD_CONTROLDATA.Object)
	{
		CharacterControlMap.Add({ECharacterControlType::Gamepad, GAMEPAD_CONTROLDATA.Object});
	}

	GetMesh()->SetRelativeLocation(FVector{0.f, 0.f, -89.f});
	GetMesh()->SetRelativeRotation(FRotator{0.f, -90.f, 0.f});

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	Camera    = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	CameraArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	FVector SpringArmLocation = CameraArm->GetRelativeLocation();
	SpringArmLocation.Z += 15.f;
	CameraArm->SetRelativeLocation(SpringArmLocation);

	JumpMaxCount = 1;

	GetCharacterMovement()->MaxWalkSpeed  = 200.f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	CombatComponent = CreateDefaultSubobject<USSCombatComponent>(TEXT("Combat Component"));
	InputActions    = CreateDefaultSubobject<USSInputConfigData>(TEXT("InputActions"));

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

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(EWeaponType::Katana, GetMesh(), FName("Weapon_rSocket"));
		CombatComponent->EquipDefenseBarrier();
	}
}

void ASSSamuraiCharacter::SetCharacterControlData(const USSCharacterControlData* ControlData)
{
	Super::SetCharacterControlData(ControlData);

	CameraArm->TargetArmLength = ControlData->TargetArmLength;
	CameraArm->SetRelativeRotation(ControlData->RelativeRotaion);
	CameraArm->bUsePawnControlRotation = ControlData->bUsePawnControlRotation;
	CameraArm->bInheritPitch           = ControlData->bInheritPitch;
	CameraArm->bInheritYaw             = ControlData->bInheritYaw;
	CameraArm->bInheritRoll            = ControlData->bInheritRoll;
	CameraArm->bDoCollisionTest        = ControlData->bDoCollisionTest;
}

// Called every frame
void ASSSamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != AbilitySystemComponent)
	{
		AbilitySystemComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_All, nullptr);
	}

	if (true == bIsLockOn
		&& nullptr != LockOnTarget)
	{
		const FVector TargetPos  = LockOnTarget->GetActorLocation() + FVector{0.0f, 0.0f, 100.f};
		const FVector Pos        = FVector(TargetPos.X, TargetPos.Y, TargetPos.Z - 150.f);
		const FRotator Rotator   = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Pos);
		const FRotator InterpRot = FMath::RInterpTo(GetControlRotation(), Rotator, GetWorld()->GetDeltaSeconds(), 5.0f);

		GetController()->SetControlRotation(InterpRot);
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

		EnhancedInputComponent->BindAction(InputActions->FindNativeInputActionByTag(FGameplayTag::RequestGameplayTag(FName("EnhancedInput.LockOn"))),
		                                   ETriggerEvent::Started, this, &ASSSamuraiCharacter::LockOn);

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
	if (true == bIsLockOn)
	{
		return;
	}

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
	bIsCrouch                            = true;
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

void ASSSamuraiCharacter::CrouchEnd()
{
	bIsCrouch                            = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void ASSSamuraiCharacter::LockOn()
{
	const FVector Start = GetActorLocation();
	//const FVector End = Start; /** (GetActorForwardVector() * -1000.f);*/

	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore = {};
	ActorsToIgnore.Add(this);

	if (nullptr != GetOwner())
	{
		ActorsToIgnore.Add(GetOwner());
	}

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = {};
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3));

	UKismetSystemLibrary::SphereTraceSingleForObjects(
	                                                  this,
	                                                  Start,
	                                                  Start,
	                                                  1000.f,
	                                                  ObjectTypes,
	                                                  false,
	                                                  ActorsToIgnore,
	                                                  EDrawDebugTrace::ForDuration,
	                                                  OutHit,
	                                                  true,
	                                                  FLinearColor::Red,
	                                                  FLinearColor::Green,
	                                                  1.f
	                                                 );

	if (nullptr != OutHit.GetActor())
	{
		LockOnTarget = Cast<ASSCharacterBase>(OutHit.GetActor());
		LockOnTarget->OnCharacterEnded.AddLambda([&]()
		{
			LockOnTarget              = nullptr;
			bIsLockOn                 = false;
			bUseControllerRotationYaw = false;
		});

		ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(LockOnTarget);
		AIPawn->SetHiddenHPBar(false);
		AIPawn->SetHiddenTargetCursor(false);

		bIsLockOn                 = true;
		bUseControllerRotationYaw = true;
	}

	else
	{
		if (nullptr != LockOnTarget)
		{
			ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(LockOnTarget);
			AIPawn->SetHiddenHPBar(true);
			AIPawn->SetHiddenTargetCursor(true);
		}

		bIsLockOn                 = false;
		bUseControllerRotationYaw = false;
	}
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

void ASSSamuraiCharacter::SetupHUDWidget(USSHUDWidget* InHUDWidget)
{
	if (nullptr != InHUDWidget)
	{
		InHUDWidget->SetMaxPlayerHP(StatComponent->GetMaxHealth());
		InHUDWidget->UpdatePlayerHPbar(StatComponent->GetMaxHealth());
		StatComponent->OnHPChanged.AddUObject(InHUDWidget, &USSHUDWidget::UpdatePlayerHPbar);
	}
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
	if (true == GetCombatComponent()->GetIsParry())
	{
		bIsLockOn = false;
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Execution));
	}

	else
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Slash));
	}
}

void ASSSamuraiCharacter::HandleSlashActionReleased()
{
	if (true == GetCombatComponent()->GetIsParry())
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Execution));
	}

	else
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Slash));
	}
}

void ASSSamuraiCharacter::HandleDefenseActionPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(ESSAbilityInputID::Defense));
}

void ASSSamuraiCharacter::HandleDefenseActionReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESSAbilityInputID::Defense));
}
