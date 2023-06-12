// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "Game/SamuraiSoul.h"
#include "UI/SSHPBarWidget.h"
#include "AI/SSEnemyAIController.h"
#include "Component/SSWidgetComponent.h"
#include "Component/SSEnemyCombatComponent.h"
#include "Component/SSCharacterStatComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

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

	HPBar = CreateDefaultSubobject<USSWidgetComponent>(TEXT("Widget"));
	HPBar->SetupAttachment(GetMesh());
	HPBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HPBAR_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContent/UI/WBP_HPBar.WBP_HPBar_C'"));

	if (true == HPBAR_WIDGET.Succeeded())
	{
		HPBar->SetWidgetClass(HPBAR_WIDGET.Class);
		HPBar->SetWidgetSpace(EWidgetSpace::Screen);
		HPBar->SetDrawSize(FVector2D(100.0f, 10.0f));
		HPBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
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

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ASSEnemyCharacter::Walk()
{
	Super::Walk();

	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

void ASSEnemyCharacter::SetupCharacterWidget(USSUserWidget* InUserWidget)
{
	Super::SetupCharacterWidget(InUserWidget);
	USSHPBarWidget* HPBarWidget = Cast<USSHPBarWidget>(InUserWidget);

	if (nullptr != HPBarWidget)
	{
		HPBarWidget->SetMaxHp(StatComponent->GetMaxHealth());
		HPBarWidget->UpdateHPBar(StatComponent->GetHealth());
		StatComponent->OnHPChanged.AddUObject(HPBarWidget, &USSHPBarWidget::UpdateHPBar);
	}
}
