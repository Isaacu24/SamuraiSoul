// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"
#include "SSCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, float /*CurrentAttribute*/);
DECLARE_MULTICAST_DELEGATE(FOnAttributeZeroDelegate);

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
	FOnAttributeChangedDelegate OnHPChanged;
	FOnAttributeChangedDelegate OnBPChanged;
	FOnAttributeZeroDelegate OnHPZero;
	FOnAttributeZeroDelegate OnBPZero;

	float GetHealth() const;
	float GetMaxHealth() const;

	float GetBalance() const;
	float GetMaxBalance() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool SetHandleGameplayEvent(FGameplayTag Tag, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
	                                    float DamageMagnitude);

	virtual void HandleDefenseHit(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	virtual void HandleBPSubtracted(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
	                                float DamageMagnitude);
	virtual void HandleRebound(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	virtual void HandleBeExecuted(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

	virtual void HandleBeAssassinated(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

	virtual void HandleDamaged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	virtual void HandleDead(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

private:
	UPROPERTY()
	TWeakObjectPtr<const USSAttributeSet> OwnerAttributeSet;

	FTimerHandle BPZeroHandle;
};
