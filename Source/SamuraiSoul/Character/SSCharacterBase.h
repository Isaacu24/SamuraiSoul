// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "DataAsset/SSAbilitySet.h"
#include "Interface/SSBehaviorInterface.h"
#include "Interface/SSCharacterWidgetInterface.h"
#include "GameFramework/Character.h"
#include "SSCharacterBase.generated.h"

class USSUserWidget;
class USSAttributeSet;
class UInputComponent;
class UGameplayEffect;
class USSCharacterData;
class USSGameplayAbility;
class UMotionWarpingComponent;
class UAbilitySystemComponent;
class USSCharacterControlData;
class UMotionWarpingComponent;
class USSCharacterStatComponent;

//Call Die()
DECLARE_MULTICAST_DELEGATE(FOnCharacterDeadDelegate);

UCLASS()
class SAMURAISOUL_API ASSCharacterBase : public ACharacter, public IAbilitySystemInterface, public ISSBehaviorInterface, public ISSCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSCharacterBase();

	virtual void SetupCharacterWidget(USSUserWidget* InUserWidget);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Die();

	virtual const FVector2D& GetMovementVector() const override;

	USSAbilitySystemComponent* GetSSAbilitySystemComponent() const
	{
		return AbilitySystemComponent;
	}

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UMotionWarpingComponent* GetMotionWarpingComponent() const
	{
		return MotionWarpComponent;
	}

	USSCharacterStatComponent* GetStatComponent() const
	{
		return StatComponent;
	}

	void SetCharacterData(USSCharacterData* Data)
	{
		if (nullptr == CharacterData)
		{
			CharacterData = Data;
		}
	}

	USSCharacterStatComponent* GetStatComponent()
	{
		return StatComponent;
	}

public:
	FOnCharacterDeadDelegate OnCharacterDead;
	FCharacterLandedDelegate OnCharacterLanded;

public:
	virtual bool IsCrouch() const override
	{
		return bIsCrouch;
	}

	virtual bool IsHit() const override
	{
		return bIsHit;
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

	virtual bool IsDown() const override
	{
		return bIsDown;
	}

	virtual void SetIsDown(bool Value) override
	{
		bIsDown = Value;
	}

	virtual bool IsDie() const override
	{
		return bIsDie;
	}

	virtual const bool GetAxisInput() const override;

	virtual FCharacterLandedDelegate& GetCharacterLandedEvnet() override
	{
		return OnCharacterLanded;
	};

protected:
	virtual void PossessedBy(AController* NewController) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void SetCharacterControlData(const USSCharacterControlData* ControlData);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterData")
	TObjectPtr<USSCharacterData> CharacterData;

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSCharacterStatComponent> StatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMotionWarpingComponent> MotionWarpComponent;

	UPROPERTY()
	FSSAbilitySet_GrantedHandles AbilitySetHandles;

protected:
	uint8 bIsCrouch : 1;
	uint8 bIsEquip : 1;;
	uint8 bIsLockOn : 1;
	uint8 bIsDefense : 1;
	uint8 bIsHit : 1;
	uint8 bIsDown: 1;
	uint8 bIsDie : 1;

	uint8 bIsAixsInput : 1;
};
