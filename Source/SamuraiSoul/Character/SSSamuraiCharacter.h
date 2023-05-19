// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "InputActionValue.h"
#include "Game/SamuraiSoul.h"
#include "Interface/SSCombatInterface.h"
#include "SSSamuraiCharacter.generated.h"

class ASSWeapon;
class UCameraComponent;
class USSInputConfigData;
class USpringArmComponent;
class UInputMappingContext;
class USSCharacterControlData;

UCLASS()
class SAMURAISOUL_API ASSSamuraiCharacter : public ASSCharacterBase, public ISSCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSSamuraiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void SetCharacterControlData(const USSCharacterControlData* ControlData) override;

	virtual USSCombatComponent* GetCombatComponent() const override
	{
		return CombatComponent;
	}

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_PlayerState() override;

	bool IsCrouch() const
	{
		return bIsCrouch;
	}

	bool IsEquip() const
	{
		return bIsEquip;
	}

	bool IsLockOn() const
	{
		return bIsLockOn;
	}

	void SwitchIsEquip()
	{
		bIsEquip = ~bIsEquip;
	}

	void Run() const;
	void UnRun() const;
	void CrouchStart();
	void CrouchEnd();

	void LockOn();

	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType CharacterControlType);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSInputConfigData> InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowParivateAccess = "true"))
	TMap<ECharacterControlType, USSCharacterControlData*> CharacterControlMap;

	UPROPERTY()
	TObjectPtr<AActor> LockOnTarget;

	ECharacterControlType ControlType;

	UPROPERTY()
	uint8 bIsCrouch : 1;

	UPROPERTY()
	uint8 bIsEquip : 1;

	UPROPERTY()
	uint8 bIsLockOn : 1;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void HandleDodgeActionPressed() const;
	void HandleDodgeActionReleased() const;

	void HandleEquipAndUnarmActionPressed() const;
	void HandleEquipAndUnarmActionReleased() const;

	void HandleJumpActionPressed() const;
	void HandleJumpActionReleased() const;

	void HandleSlashActionPressed();
	void HandleSlashActionReleased() const;

	void HandleDefenseActionPressed() const;
	void HandleDefenseActionReleased() const;
};
