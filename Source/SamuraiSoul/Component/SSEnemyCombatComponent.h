// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/SSCombatComponent.h"
#include "SSEnemyCombatComponent.generated.h"

/**
 *
 */
UCLASS()
class SAMURAISOUL_API USSEnemyCombatComponent : public USSCombatComponent
{
	GENERATED_BODY()

public:
	USSEnemyCombatComponent();

	virtual void BeginPlay() override;

	void SetEnemyWeapon() const;
	void AttackByAI() const;

protected:
	virtual void Hit(AActor* InActor) override;

	virtual void Parry(AActor* Opponent) override;
	virtual void Rebound(AActor* Opponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> SlashAbility;
};
