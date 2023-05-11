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
class ISSCombatInterface;
class ASSWeapon_DefenseBarrier;

//DECLARE_DELEGATE_OneParam(FCombatDelegate, EWeaponType Type);
//DECLARE_DELEGATE(FExecuteDelegate);

DECLARE_DELEGATE(FCombatDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class SAMURAISOUL_API USSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USSCombatComponent();

	FCombatDelegate AttackEvent;
	FCombatDelegate HitEvent;
	FCombatDelegate DeathEvent;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipWeapon(USceneComponent* InParent, FName InSocketName);
	void EquipDefenseBarrier();
	void SetEnemyWeapon();

	void Hit();
	void Die();
	void ChangeRagdoll();

	void Parry(ISSCombatInterface* Opponent);
	void Rebound(ISSCombatInterface* Opponent);

	void ParryEnd(UAnimMontage* Montage, bool bInterrupted);
	void ReboundEnd(UAnimMontage* Montage, bool bInterrupted);

	void OnDefense();
	void OffDefense();
	void ChangeDefenseType(EDefenseType Type);

	void OnWeapon();
	void OffWeapon();

	bool GetIsParry() const
	{
		return IsParry;
	}

	bool GetIsRebound() const
	{
		return IsRebound;
	}

	ISSCombatInterface* GetInstigator() const
	{
		return Instigator;
	}


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon_DefenseBarrier> DefenseBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ExecutionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ExecutedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ParryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ReboundMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> ExecutionAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> ExecutedAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ISSCombatInterface> Instigator;

	UPROPERTY()
	uint8 IsParry : 1;

	UPROPERTY()
	uint8 IsRebound : 1;
};
