// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "Interface/SSBehaviorInterface.h"
#include <MotionWarpingComponent.h>
#include "GameFramework/Character.h"
#include "SSCharacterBase.generated.h"

class USSAttributeSet;
class UInputComponent;
class UGameplayEffect;
class USSGameplayAbility;
class UMotionWarpingComponent;
class UAbilitySystemComponent;
class USSCharacterControlData;

DECLARE_MULTICAST_DELEGATE(FCharacterEndedDelegate);

UENUM()
enum class ECharacterControlType : uint8
{
	Keyboard,
	Gamepad
};

UCLASS()
class SAMURAISOUL_API ASSCharacterBase : public ACharacter, public IAbilitySystemInterface, public ISSBehaviorInterface
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

	void Die() const;

	virtual UAbilitySystemComponent* ASSCharacterBase::GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	UMotionWarpingComponent* GetMotionWarpingComponent() const
	{
		return MotionWarpComponent;
	}

	float GetHealth() const;

	FCharacterEndedDelegate OnCharacterEnded;

public:
	virtual bool IsCrouch() const override
	{
		return bIsCrouch;
	}

	virtual bool IsEquip() const override
	{
		return bIsEquip;
	}

	virtual bool IsLockOn() const override
	{
		return bIsLockOn;
	}

	virtual void SwitchIsEquip() override
	{
		bIsEquip = ~bIsEquip;
	}

	virtual bool IsDefense() const override
	{
		return bIsDefense;
	}

	virtual void SwitchIsDefense() override
	{
		bIsDefense = ~bIsDefense;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void SetCharacterControlData(const USSCharacterControlData* ControlData);

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USSAttributeSet> Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<USSGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMotionWarpingComponent> MotionWarpComponent;

protected:
	uint8 bIsCrouch : 1;
	uint8 bIsEquip : 1;;
	uint8 bIsLockOn : 1;
	uint8 bIsDefense : 1;
};
