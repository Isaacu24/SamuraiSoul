// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SamuraiSoul.h"
#include "SSCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/SSCharacterHUDInterface.h"
#include "Interface/SSCombatableInterface.h"
#include "SSSamuraiCharacter.generated.h"

class ASSWeapon;
class UInputComponent;
class UCameraComponent;
class USSInputConfigData;
class USSSamuraiHUDWidget;
class USpringArmComponent;
class UInputMappingContext;
class USSCharacterControlData;

UCLASS()
class SAMURAISOUL_API ASSSamuraiCharacter : public ASSCharacterBase, public ISSCharacterHUDInterface, public ISSCombatableInterface
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_PlayerState() override;

	virtual const FVector2D& GetMovementVector() const override;

	virtual void Die() override;

	void Run();
	void UnRun();
	void CrouchStart();
	void CrouchEnd();

	void LockOnSwitch();
	void LockOn();
	void LockOff();

	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType CharacterControlType);

	virtual void SetupHUDWidget(USSHUDWidget* InHUDWidget) override;
	virtual void SetBossDataInHUD(ASSEnemyBossCharacter* Boss) override;

	virtual EAttackType GetWeaponAttakType() const override;
	virtual void SetWeaponAttackType(EAttackType InType) override;

	UFUNCTION()
	virtual void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex,
	                                   bool bFromSweep,
	                                   const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCapsuleOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	virtual bool GetCanEnemyExecution() const override
	{
		return CanEnemyExecution;
	};

	virtual void SetCanEnemyExecution(bool Value) override
	{
		CanEnemyExecution = Value;
	};

	virtual bool GetCanEnemyAssassination() const override
	{
		return CanEnemyAssassination;
	}

	virtual void SetCanEnemyAssassination(bool Value) override
	{
		CanEnemyAssassination = Value;
	};

private:
	void Move(const FInputActionValue& Value);
	void MoveEnd(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSInputConfigData> InputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowParivateAccess = "true"))
	TMap<ECharacterControlType, USSCharacterControlData*> CharacterControlMap;

	UPROPERTY()
	TObjectPtr<AActor> LockOnTarget;

	ECharacterControlType ControlType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class ULevelSequence> LevelSequence;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class ULevelSequencePlayer> LevelSequencePlayer;

	UPROPERTY()
	FVector2D MovementVector;

	UPROPERTY()
	USSSamuraiHUDWidget* MyHUD;

	bool CanEnemyExecution;
	bool CanEnemyAssassination;
};
