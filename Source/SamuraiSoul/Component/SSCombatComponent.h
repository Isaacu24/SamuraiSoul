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
	void TakeGameplayEffect(const TSubclassOf<UGameplayEffect> Effect) const;

	virtual void Parry(AActor* InActor);
	virtual void Rebound();
	virtual void BeExecuted(int8 RandomNumber);

	void OnDefense() const;
	void OffDefense() const;
	void ChangeDefenseState(EDefenseState Type) const;

	void OnWeapon() const;
	void OffWeapon() const;

	AActor* GetTarget() const
	{
		return Target;
	}

	void SetTarget(AActor* InActor)
	{
		Target = InActor;
	}

	int8 GetExecutionNumber() const
	{
		return ExecutionNumber;
	}

protected:
	virtual void Attack(AActor* InActor, const FHitResult& HitResult) const;
	virtual void Hit();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon_DefenseBarrier> DefenseBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> ParryAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ParryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ReboundMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> BeExecutedEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> ReboundEffect;

	UPROPERTY()
	TObjectPtr<AActor> Target;

	UPROPERTY()
	int8 ExecutionNumber;
};
