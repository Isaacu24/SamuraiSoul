// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SamuraiSoul.h"
#include "SSCharacterBase.h"
#include "InputActionValue.h"
#include "SSSamuraiCharacter.generated.h"

class USSCharacterControlData;
class UCameraComponent;
class USSInputConfigData;
class USpringArmComponent;
class UInputMappingContext;
class ASSWeapon;

DECLARE_DELEGATE(FAnimDelegate);

UCLASS()
class SAMURAISOUL_API ASSSamuraiCharacter : public ASSCharacterBase
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

	void SwitchIsEquip()
	{
		bIsEquip = ~bIsEquip;
	}

	void Run();
	void UnRun();
	void CrouchStart();
	void CrouchEnd();

	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType CharacterControlType);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSInputConfigData> InputActions;

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowParivateAccess = "true"))
	TMap<ECharacterControlType, USSCharacterControlData*> CharacterControlMap;
	
	ECharacterControlType ControlType;

	UPROPERTY()
	uint8 bIsCrouch : 1;

	UPROPERTY()
	uint8 bIsEquip : 1;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void HandleDodgeActionPressed();
	void HandleDodgeActionReleased();

	void HandleEquipAndUnarmActionPressed();
	void HandleEquipAndUnarmActionReleased();

	void HandleJumpActionPressed();
	void HandleJumpActionReleased();

	void HandleSlashActionPressed();
	void HandleSlashActionReleased();

	void HandleDefenseActionPressed();
	void HandleDefenseActionReleased();
};

