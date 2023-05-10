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

	FCombatDelegate ExecutionEvent;
	FCombatDelegate ExecutedEvent;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipWeapon(USceneComponent* InParent, FName InSocketName);
	void EquipDefenseBarrier();
	void SetEnemyWeapon();

	void Hit();
	void Die();
	void ChangeRagdoll();

	void Execution();
	void Executed();

	void OnDefense();
	void OffDefense();

	//ISSCombatInterface* GetEnemy()
	//{
	//	return Enemy;
	//}

	//void SetEnemy(ISSCombatInterface* Character)
	//{
	//	Enemy = Character;
	//}

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> DefenseBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ExecutionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ExecutedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> ExecutionAbility;

	//UPROPERTY()
	//TObjectPtr<ISSCombatInterface> Enemy;
};
