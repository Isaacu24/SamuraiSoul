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

#include "EngineUtils.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Interface/SSTargetableInterface.h"

#include "Abilities/SSAbilitySystemComponent.h"
#include "Component/SSCombatComponent.h"
#include "SSCharacterControlData.h"
#include "SSEnemyBossCharacter.h"
#include "Component/SSCharacterStatComponent.h"
#include "UI/SSHUDWidget.h"
#include "SSGameplayTags.h"
#include "GameData/SSSpawnEnemyData.h"
#include "Input/SSInputComponent.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "UI/SSSamuraiHUDWidget.h"

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
		KEYBOARD_CONTROLDATA(TEXT("/Script/SamuraiSoul.SSCharacterControlData'/Game/MyContent/DataAsset/Character/Samurai/Control/DA_Keyboard.DA_Keyboard'"));

	static ConstructorHelpers::FObjectFinder<USSCharacterControlData>
		GAMEPAD_CONTROLDATA(TEXT("/Script/SamuraiSoul.SSCharacterControlData'/Game/MyContent/DataAsset/Character/Samurai/Control/DA_Gamepad.DA_Gamepad'"));

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
	InputConfig     = CreateDefaultSubobject<USSInputConfigData>(TEXT("InputConfig"));

	ControlType = ECharacterControlType::Keyboard;
}

// Called when the game starts or when spawned
void ASSSamuraiCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASSSamuraiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(EWeaponType::Katana, GetMesh(), FName("Weapon_rSocket"));
		CombatComponent->EquipDefenseBarrier();
	}

	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bDisableLookAtInput   = true;
	Settings.bDisableMovementInput = true;
	Settings.bHideHud              = true;

	ALevelSequenceActor* SequenceActor;

	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Settings, SequenceActor);
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
		AActor* TargetActor = Cast<AActor>(LockOnTarget);

		const FVector TargetPos  = TargetActor->GetActorLocation() + FVector{0.0f, 0.0f, 25.f};
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

	USSInputComponent* SSInputComponent = CastChecked<USSInputComponent>(PlayerInputComponent);

	SetCharacterControl(ControlType);

	//for AnimMontage Cancel.
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_MoveTag, ETriggerEvent::Completed, this, &ASSSamuraiCharacter::MoveEnd);

	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_MoveTag, ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::Move);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_LookTag, ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::Look);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_RunTag, ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::Run);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_UnRunTag, ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::UnRun);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_CrouchStartTag, ETriggerEvent::Triggered, this,
	                                   &ASSSamuraiCharacter::CrouchStart);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_CrouchEndTag, ETriggerEvent::Triggered, this, &ASSSamuraiCharacter::CrouchEnd);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_LockOnTag, ETriggerEvent::Completed, this, &ASSSamuraiCharacter::LockOnSwitch);
	SSInputComponent->BindNativeAction(InputConfig, FSSGameplayTags::Get().Input_ChangeControlTag, ETriggerEvent::Triggered, this,
	                                   &ASSSamuraiCharacter::ChangeCharacterControl);

	SSInputComponent->BindAbilityActions(InputConfig, this, &ASSSamuraiCharacter::Input_AbilityInputTagPressed,
	                                     &ASSSamuraiCharacter::Input_AbilityInputTagReleased);
}

void ASSSamuraiCharacter::OnRep_PlayerState()
{
	//Replication no idea
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

const FVector2D& ASSSamuraiCharacter::GetMovementVector() const
{
	return MovementVector;
}

void ASSSamuraiCharacter::Die()
{
	Super::Die();

	LockOff();
}

void ASSSamuraiCharacter::PostDeath()
{
	Super::PostDeath();
}

EAttackType ASSSamuraiCharacter::GetWeaponAttakType() const
{
	return CombatComponent->GetWeapon()->GetAttackType();
}

void ASSSamuraiCharacter::SetWeaponAttackType(EAttackType InType)
{
	CombatComponent->GetWeapon()->SetAttackType(InType);
}

void ASSSamuraiCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	MovementVector = Value.Get<FVector2D>();

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

		UE_LOG(LogTemp, Error, TEXT("FowardBack: %f"), MovementVector.Y);
		UE_LOG(LogTemp, Error, TEXT("RightLeft: %f"), MovementVector.X);
	}

	bIsAixsInput = true;
	UE_LOG(LogTemp, Warning, TEXT("AixsInput"));
}

void ASSSamuraiCharacter::MoveEnd(const FInputActionValue& Value)
{
	bIsAixsInput = false;
	UE_LOG(LogTemp, Warning, TEXT("Not AixsInput"));
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

void ASSSamuraiCharacter::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	ensure(GetSSAbilitySystemComponent());

	GetSSAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
}

void ASSSamuraiCharacter::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	ensure(GetSSAbilitySystemComponent());

	GetSSAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
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

void ASSSamuraiCharacter::LockOnSwitch()
{
	if (false == bIsLockOn)
	{
		LockOn();
	}

	else
	{
		LockOff();
	}
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
	                                                  1500.f,
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

	if (nullptr == OutHit.GetActor())
	{
		LockOff();
	}

	LockOnTarget = OutHit.GetActor();

	ISSTargetableInterface* TargetPawn = Cast<ISSTargetableInterface>(LockOnTarget);

	if (nullptr == TargetPawn)
	{
		return;
	}

	TargetPawn->GetTargetingEndedDelegate().BindUObject(this, &ASSSamuraiCharacter::LockOff);
	TargetPawn->VisibleTargetUI();

	bIsLockOn                 = true;
	bUseControllerRotationYaw = true;
}

void ASSSamuraiCharacter::LockOff()
{
	if (nullptr == LockOnTarget)
	{
		return;
	}

	ISSTargetableInterface* TargetPawn = Cast<ISSTargetableInterface>(LockOnTarget);
	TargetPawn->HideTargetUI();

	LockOnTarget = nullptr;

	bIsLockOn                 = false;
	bUseControllerRotationYaw = false;
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
	MyHUD = Cast<USSSamuraiHUDWidget>(InHUDWidget);

	if (nullptr != MyHUD)
	{
		MyHUD->SetMaxPlayerHP(StatComponent->GetMaxHealth());
		MyHUD->UpdatePlayerHPbar(StatComponent->GetHealth());
		MyHUD->SetMaxPlayerBP(StatComponent->GetMaxBalance());

		StatComponent->OnHPChanged.AddUObject(MyHUD, &USSSamuraiHUDWidget::UpdatePlayerHPbar);
		StatComponent->OnBPChanged.AddUObject(MyHUD, &USSSamuraiHUDWidget::UpdatePlayerBPGauge);
		OnCharacterDead.AddUObject(MyHUD, &USSSamuraiHUDWidget::OnDeathScreen);
	}
}

void ASSSamuraiCharacter::SetBossDataInHUD(ASSEnemyBossCharacter* Boss)
{
	if (nullptr != MyHUD)
	{
		MyHUD->SetVisibilityBossHUD(ESlateVisibility::Visible);

		MyHUD->SetBossName(Boss->GetBossName());
		MyHUD->SetMaxBossHP(Boss->GetStatComponent()->GetMaxHealth());
		MyHUD->UpdateBossHPbar(Boss->GetStatComponent()->GetHealth());

		Boss->GetStatComponent()->OnHPChanged.AddUObject(MyHUD, &USSSamuraiHUDWidget::UpdateBossHPbar);
		Boss->GetStatComponent()->OnBPChanged.AddUObject(MyHUD, &USSSamuraiHUDWidget::UpdateBossBPGauge);
		Boss->OnCharacterDead.AddUObject(MyHUD, &USSSamuraiHUDWidget::SetHiddenBossHUD);
	}
}
