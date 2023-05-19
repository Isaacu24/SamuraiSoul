// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
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

UENUM()
enum class ECharacterControlType : uint8
{
	Keyboard,
	Gamepad
};

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

	void Die();

	virtual UAbilitySystemComponent* ASSCharacterBase::GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	UMotionWarpingComponent* GetMotionWarpingComponent() const
	{
		return MotionWarpComponent;
	}

	bool IsDefense() const
	{
		return bIsDefense;
	}

	void SwitchIsDefense()
	{
		bIsDefense = ~bIsDefense;
	}

	float GetHealth() const;

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

	UPROPERTY()
	uint8 bIsDefense : 1;
};
