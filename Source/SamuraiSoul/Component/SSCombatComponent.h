// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SamuraiSoul.h"
#include "Components/ActorComponent.h"
#include "SSCombatComponent.generated.h"

class ASSWeapon;
class USceneComponent;
class UGameplayEffect;
class UGameplayAbility;
class ASSCharacterBase;
class ASSWeapon_DefenseBarrier;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class SAMURAISOUL_API USSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USSCombatComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipWeapon(EWeaponType Type, USceneComponent* InParent, FName InSocketName);
	void EquipDefenseBarrier();

	void ActivateAbility(const TSubclassOf<UGameplayAbility> Ability) const;

	void Parry(AActor* Opponent);
	void Rebound(AActor* Opponent);

	void ParryEnd(UAnimMontage* Montage, bool bInterrupted);
	void ReboundEnd(UAnimMontage* Montage, bool bInterrupted);

	void OnDefense() const;
	void OffDefense() const;
	void ChangeDefenseState(EDefenseState Type) const;

	void OnWeapon() const;
	void OffWeapon() const;

	void AddOrUpdateWarpTarget(const FMotionWarpingTarget& Target) const;

	bool GetIsParry() const
	{
		return IsParry;
	}

	bool GetIsRebound() const
	{
		return IsRebound;
	}

	AActor* GetTarget() const
	{
		return Target;
	}

	void SetTarget(AActor* Actor)
	{
		Target = Actor;
	}

protected:
	virtual void Attack(AActor* InActor, const FHitResult& HitResult) const;
	virtual void Hit(const FHitResult& HitResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon_DefenseBarrier> DefenseBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ParryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ReboundMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> ExecutedAbility;

	UPROPERTY()
	uint8 IsParry : 1;

	UPROPERTY()
	uint8 IsRebound : 1;

	UPROPERTY()
	TObjectPtr<AActor> Target;
};
