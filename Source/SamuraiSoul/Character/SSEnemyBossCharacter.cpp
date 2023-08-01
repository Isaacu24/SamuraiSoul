// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSEnemyBossCharacter.h"

#include "Abilities/SSAbilitySystemComponent.h"
#include "AI/SSEnemyBossAIController.h"
#include "Animation/SSEnemyBossAnimInstance.h"
#include "Component/SSCharacterStatComponent.h"
#include "Component/SSEnemyBossCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
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

	DissolveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Dissolve Timeline"));

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

void ASSEnemyBossCharacter::UpdateMaterialDissolve(float DissolveTime)
{
	if (DynamicDissolveMaterialInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("This is null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("dissolve : %f"), DissolveTime);
	DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dissolve"), DissolveTime);
}

void ASSEnemyBossCharacter::EndMaterialDissolve()
{
	Destroy();

	StatComponent->DestroyComponent();
	CombatComponent->DestroyComponent();
	AbilitySystemComponent->DestroyComponent();
	DissolveTimeline->DestroyComponent();
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
		int Result = FMath::RandRange(1, Count);

		CombatComponent->SpecialAttackByAI(AICharacterStatData->SpectialAttackTags[Result]);
	}
}

void ASSEnemyBossCharacter::Die()
{
	Super::Die();

	ASSEnemyBossAIController* AIController = Cast<ASSEnemyBossAIController>(GetController());

	if (nullptr != AIController)
	{
		AIController->SetDead(true);
	}

	if (nullptr == DissolveCurve
		|| nullptr == DissolveTimeline
		|| nullptr == DissolveMaterialInstance)
	{
		return;
	}

	DynamicDissolveMaterialInstance = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);

	const int32 MaterialCount = GetMesh()->GetNumOverrideMaterials();

	for (int i = 0; i < MaterialCount; ++i)
	{
		GetMesh()->SetMaterial(i, DynamicDissolveMaterialInstance);
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Disslove"), -0.5f);
	}

	FOnTimelineFloat DissolveTrack;
	DissolveTrack.BindDynamic(this, &ThisClass::UpdateMaterialDissolve);
	DissolveTimeline->AddInterpFloat(DissolveCurve, DissolveTrack);

	FOnTimelineEvent TimelineEndEvent;
	TimelineEndEvent.BindDynamic(this, &ThisClass::EndMaterialDissolve);
	DissolveTimeline->SetTimelineFinishedFunc(TimelineEndEvent);
	DissolveTimeline->Play();
}

void ASSEnemyBossCharacter::RangeAttack()
{
	TArray<FHitResult> OutHits = {};
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange  = 100.0f;
	const float AttackRadius = 400.0f;

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End   = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_GameTraceChannel4,
	                                                   FCollisionShape::MakeSphere(AttackRadius),
	                                                   Params);

	for (const FHitResult& HitResult : OutHits)
	{
		ISSCombatableInterface* CombatPawn = Cast<ISSCombatableInterface>(HitResult.GetActor());

		if (nullptr != CombatPawn)
		{
			CombatPawn->GetCombatComponent()->Attack(HitResult.GetActor(), HitResult);
		}
	}

#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin   = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor        = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false,
	                 1.0f);

#endif
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
