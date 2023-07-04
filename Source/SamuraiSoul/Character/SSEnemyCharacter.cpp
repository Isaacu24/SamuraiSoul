// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "Game/SamuraiSoul.h"
#include "AI/SSEnemyAIController.h"
#include "Component/SSWidgetComponent.h"
#include "Component/SSEnemyCombatComponent.h"
#include "Component/SSCharacterStatComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/BoxComponent.h"
#include "UI/SSEnemyHUDWidget.h"

ASSEnemyCharacter::ASSEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/MyContent/Mesh/Enemy/Samurai/SK_EnemySamurai_Katana.SK_EnemySamurai_Katana'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		ANIM_ENEMY(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_ENEMY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_ENEMY.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{0.f, 0.f, -89.f});
	GetMesh()->SetRelativeRotation(FRotator{0.f, -90.f, 0.f});

	AIControllerClass = ASSEnemyAIController::StaticClass();
	AutoPossessAI     = EAutoPossessAI::PlacedInWorldOrSpawned;

	EnemyHUD = CreateDefaultSubobject<USSWidgetComponent>(TEXT("Enemy HUD"));
	EnemyHUD->SetupAttachment(GetMesh());
	EnemyHUD->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget>
		EnemyHUD_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/WBP_SSEnemyHUD.WBP_SSEnemyHUD_C'"));

	if (true == EnemyHUD_WIDGET.Succeeded())
	{
		EnemyHUD->SetWidgetClass(EnemyHUD_WIDGET.Class);
		EnemyHUD->SetWidgetSpace(EWidgetSpace::Screen);
		EnemyHUD->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	AssassinationCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Assassination Collider"));
	AssassinationCollider->SetCollisionProfileName("AssassinationCollision");
	AssassinationCollider->SetupAttachment(GetMesh());
	AssassinationCollider->SetBoxExtent(FVector{100.f, 100.f, 100.f});
	AssassinationCollider->SetRelativeLocation(FVector(0.0f, -140.f, 110.0f));
}

void ASSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(EWeaponType::Katana, GetMesh(), FName("Weapon_rSocket"));
		CombatComponent->EquipDefenseBarrier();
		CombatComponent->SetEnemyWeapon();
	}
}

void ASSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSEnemyCharacter::Die()
{
	Super::Die();
}

void ASSEnemyCharacter::SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished)
{
	Super::SetAIAttackDelegate(InOnAttackFinished);
}

void ASSEnemyCharacter::AttackByAI()
{
	if (nullptr != CombatComponent)
	{
		CombatComponent->AttackByAI();
	}
}

void ASSEnemyCharacter::SpectialAttackByAI(const FGameplayTag& Tag)
{
	if (nullptr != CombatComponent)
	{
		CombatComponent->SpecialAttackByAI(Tag);
	}
}

void ASSEnemyCharacter::EquipUnarm()
{
	if (nullptr != CombatComponent)
	{
		CombatComponent->Equip();
	}
}

void ASSEnemyCharacter::Run()
{
	Super::Run();

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void ASSEnemyCharacter::Walk()
{
	Super::Walk();

	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void ASSEnemyCharacter::VisibleTargetUI()
{
	Super::VisibleTargetUI();

	if (nullptr != EnemyHUD)
	{
		EnemyHUD->SetHiddenInGame(false);
	}
}

void ASSEnemyCharacter::HideTargetUI()
{
	Super::HideTargetUI();

	if (nullptr != EnemyHUD)
	{
		EnemyHUD->SetHiddenInGame(true);
	}
}

void ASSEnemyCharacter::SetupCharacterWidget(USSUserWidget* InUserWidget)
{
	Super::SetupCharacterWidget(InUserWidget);
	USSEnemyHUDWidget* HUDwidget = Cast<USSEnemyHUDWidget>(InUserWidget);

	if (nullptr != HUDwidget)
	{
		HUDwidget->SetMaxEnemyHP(StatComponent->GetMaxHealth());
		HUDwidget->SetMaxEnemyBPGauge(StatComponent->GetMaxBalance());
		HUDwidget->UpdateEnemyHPbar(StatComponent->GetHealth());

		StatComponent->OnHPChanged.AddUObject(HUDwidget, &USSEnemyHUDWidget::UpdateEnemyHPbar);
		StatComponent->OnBPChanged.AddUObject(HUDwidget, &USSEnemyHUDWidget::UpdateEnemyBPGauge);
		StatComponent->OnBPZero.AddUObject(HUDwidget, &USSEnemyHUDWidget::OffEnemyBPGauge);
	}
}


void ASSEnemyCharacter::SetParry(bool Value)
{
	Super::SetParry(Value);

	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetParry(Value);
	}
}

void ASSEnemyCharacter::SetHit(bool Value)
{
	Super::SetHit(Value);

	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetHit(Value);
	}
}

void ASSEnemyCharacter::SetDead(bool Value)
{
	Super::SetDead(Value);

	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetDead(Value);
	}
}

void ASSEnemyCharacter::SetRebound(bool Value)
{
	Super::SetRebound(Value);

	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetRebound(Value);
	}
}

void ASSEnemyCharacter::SetEquip(bool Value)
{
	Super::SetEquip(Value);

	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetEquip(Value);
	}
}

void ASSEnemyCharacter::SetBeExecuted(bool Value)
{
	Super::SetBeExecuted(Value);

	ASSEnemyAIController* AIController = Cast<ASSEnemyAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetBeExecuted(Value);
	}
}
