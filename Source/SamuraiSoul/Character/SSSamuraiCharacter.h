// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "InputActionValue.h"
#include "SSSamuraiCharacter.generated.h"

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

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
		bIsEquip = !bIsEquip;
	}

	void Run();
	void UnRun();
	void CrouchStart();
	void CrouchEnd();

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> Arm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USSInputConfigData> InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY()
	bool bIsCrouch = false;

	UPROPERTY()
	bool bIsEquip = false;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void HandleRunActionPressed();
	void HandleRunActionReleased();

	void HandleDodgeActionPressed();
	void HandleDodgeActionReleased();

	void HandleEquipAndUnarmActionPressed();
	void HandleEquipAndUnarmActionReleased();

	void HandleCrouchActionPressed();
	void HandleCrouchActionReleased();

	void HandleJumpActionPressed();
	void HandleJumpActionReleased();

	void HandleSlashActionPressed();
	void HandleSlashActionReleased();

	void HandleDefenseActionPressed();
	void HandleDefenseActionReleased();
};
