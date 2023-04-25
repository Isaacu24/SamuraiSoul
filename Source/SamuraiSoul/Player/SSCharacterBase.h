// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "SSCharacterBase.generated.h"

class UAbilitySystemComponent;
class USSAttributeSet;
class UGameplayEffect;
class USSGameplayAbility;
class UInputComponent;

DECLARE_DELEGATE(FAnimDelegate);

UCLASS()
class SAMURAISOUL_API ASSCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSCharacterBase();

	virtual void InitializeAttributes();
	virtual void GiveAbilities();
	virtual void PossessedBy(AController* NewController) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void DamageCheck();

	virtual void AttackFail();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	bool IsDefense() const
	{
		return bIsDefense;
	}

	void SwitchIsDefense()
	{
		bIsDefense = !bIsDefense;
	}

	FAnimDelegate HitDelegate;
	FAnimDelegate DeathDelegate;
	FAnimDelegate AttackFailDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USSAttributeSet> Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<USSGameplayAbility>> DefaultAbilities;

	UPROPERTY()
	bool bIsDefense = false;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DamageEffect;
};