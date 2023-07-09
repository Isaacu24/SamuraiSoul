// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSEnemyBossCharacter.h"

#include "AI/SSAI.h"
#include "AI/SSEnemyBossAIController.h"
#include "Animation/SSEnemyBossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/SSEnemyBossCombatComponent.h"
#include "DataAsset/SSAICharacterStatData.h"

ASSEnemyBossCharacter::ASSEnemyBossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<USSEnemyBossCombatComponent>(TEXT("Combat Component"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/BossyEnemy/SkeletalMesh/SK_Mannequin_UE4_WithWeapon.SK_Mannequin_UE4_WithWeapon'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		ANIM_ENEMY(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/Character/AI/AB_SSEnemyBossCharacter.AB_SSEnemyBossCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_ENEMY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_ENEMY.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{0.f, 0.f, -88.5f});
	GetMesh()->SetRelativeRotation(FRotator{0.f, -90.f, 0.f});

	AIControllerClass = ASSEnemyBossAIController::StaticClass();
	AutoPossessAI     = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASSEnemyBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSEnemyBossCharacter::StopAI()
{
	Super::StopAI();

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void ASSEnemyBossCharacter::RunAI()
{
	Super::RunAI();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ASSEnemyBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASSEnemyBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (nullptr != CombatComponent)
	{
		CombatComponent->EquipWeapon(EWeaponType::Katana, GetMesh(), FName("WeaponStart"));
		CombatComponent->SetEnemyWeapon();
	}

	USSEnemyBossAnimInstance* BossAnim = Cast<USSEnemyBossAnimInstance>(GetMesh()->GetAnimInstance());
	check(BossAnim);

	BossAnim->OnMontageEnded.AddDynamic(this, &ASSEnemyBossCharacter::OnBattleEntranceMontageEnded);
}

void ASSEnemyBossCharacter::BattleEntrance()
{
	ASSEnemyBossAIController* BossController = Cast<ASSEnemyBossAIController>(GetController());

	if (nullptr != BossController)
	{
		BossController->BattleEntrance();
	}

	USSEnemyBossAnimInstance* BossAnimInstance = Cast<USSEnemyBossAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr != BossAnimInstance)
	{
		BossAnimInstance->PlayBattleEntrance();
	}
}

void ASSEnemyBossCharacter::AttackByAI()
{
	if (nullptr == CombatComponent)
	{
		return;
	}

	float AttackRadius = AICharacterStatData->AIAttackRange * 0.5f;

	if (AttackRadius <= Distance)
	{
		CombatComponent->SpecialAttackByAI(AICharacterStatData->SpectialAttackTags[0]);
	}

	else
	{
		int Count  = AICharacterStatData->SpectialAttackTags.Num() - 1;
		int Result = FMath::RandRange(0, Count);

		CombatComponent->SpecialAttackByAI(AICharacterStatData->SpectialAttackTags[Result]);
	}
}

EAttackType ASSEnemyBossCharacter::GetWeaponAttakType() const
{
	return CombatComponent->GetWeapon()->GetAttackType();
}

void ASSEnemyBossCharacter::SetWeaponAttackType(EAttackType InType)
{
	CombatComponent->GetWeapon()->SetAttackType(InType);
}

void ASSEnemyBossCharacter::OnBattleEntranceMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnBattleEtranced.Broadcast();
}
