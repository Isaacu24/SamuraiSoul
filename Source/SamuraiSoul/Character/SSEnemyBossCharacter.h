// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSEnemyCharacterBase.h"
#include "DataAsset/SSAICharacterStatData.h"
#include "SSEnemyBossCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FBossCharacterMontageEnded);

class USSEnemyBossCombatComponent;

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyBossCharacter : public ASSEnemyCharacterBase
{
	GENERATED_BODY()

public:
	ASSEnemyBossCharacter();

	virtual USSCombatComponent* GetCombatComponent() const override
	{
		return static_cast<USSCombatComponent*>(CombatComponent);
	}

	virtual void Tick(float DeltaTime) override;

	void SetName(const FString& InName)
	{
		Name = InName;
	}

	const FString& GetBossName() const
	{
		return Name;
	}

	virtual void StopAI() override;
	virtual void RunAI() override;

	virtual void BattleEntrance();
	virtual void AttackByAI() override;

	FORCEINLINE void SetDistanceToTarget(float Value)
	{
		Distance = Value;
	}

	virtual void RangeAttack();

	virtual EAttackType GetWeaponAttakType() const override;
	virtual void SetWeaponAttackType(EAttackType InType) override;

	UFUNCTION()
	void OnBattleEntranceMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	FBossCharacterMontageEnded OnBattleEtranced;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	float Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSEnemyBossCombatComponent> CombatComponent;
};
