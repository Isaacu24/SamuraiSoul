// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "SSSamuraiCharacter.generated.h"

UCLASS()
class SAMURAISOUL_API ASSSamuraiCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSSamuraiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class USSGameplayAbility>> DefaultAbilities;

	bool IsCrouch() const
	{
		return bIsCrouch;
	}

	bool IsEquip() const
	{
		return bIsEquip;
	}

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> Arm;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class USSAttributeSet> Attributes;

	UPROPERTY()
	bool bIsCrouch = false;

	UPROPERTY()
	bool bIsEquip = false;

	UPROPERTY()
	FTimerHandle DodgeTimerHandle;

	UPROPERTY()
	FTimerHandle DodgeEndTimerHandle;

private:
	void FowardBackMove(float Value);
	void RightLeftMove(float Value);

	void Equip();

	void Dodge();

	void Run();
	void UnRun();

	void CrouchStart();
	void CrouchEnd();
};
