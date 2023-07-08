// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/SSEnemyCombatBaseComponent.h"
#include "SSEnemyCombatComponent.generated.h"

/**
 *
 */
UCLASS()
class SAMURAISOUL_API USSEnemyCombatComponent : public USSEnemyCombatBaseComponent
{
	GENERATED_BODY()

public:
	USSEnemyCombatComponent();

	virtual void BeginPlay() override;
	void AttackByAI() const override;

	virtual void EquipUnarm();

	virtual void Parry(AActor* InActor) override;
	virtual void Rebound() override;

protected:
	virtual void Hit(EAttackType InType) override;
	virtual void BeExecuted(int8 RandomNumber) override;
	virtual void BeAssassinated(int8 RandomNumber) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> BeExecutedEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> BeAssassinatedEffect;
};
