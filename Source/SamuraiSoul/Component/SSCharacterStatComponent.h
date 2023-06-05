// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"
#include "SSCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHP*/);
DECLARE_MULTICAST_DELEGATE(FOnCharacterDeadDelegate);

class USSAttributeSet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAMURAISOUL_API USSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USSCharacterStatComponent();

	void SetAbilityDelegates();

public:
	FOnHPChangedDelegate OnHPChanged;
	FOnCharacterDeadDelegate OnCharacterDead;

	float GetHealth() const;
	float GetMaxHealth() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual bool SetHandleGameplayEvent(FGameplayTag Tag, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
	                                    float DamageMagnitude);

	virtual void HandleDamaged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	virtual void HandleDead(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	virtual void HandleBeExecuted(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	virtual void HandleRebound(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

private:
	TWeakObjectPtr<const USSAttributeSet> OwnerAttributeSet;
};
