// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacterBase.h"
#include "SSSamuraiCharacter.generated.h"

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

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> Arm;

	UPROPERTY()
	bool bIsCrouch = false;

	UPROPERTY()
	bool bIsEquip = false;

	UPROPERTY()
		bool bIsSlash = false;

	UPROPERTY()
	FTimerHandle DodgeTimerHandle;

	UPROPERTY()
	FTimerHandle DodgeEndTimerHandle;

	UPROPERTY()
		TObjectPtr<class USSSamuraiAnimInstance> MyAniminstance;
	
private:
	void FowardBackMove(float Value);
	void RightLeftMove(float Value);

	void Equip();

	void Dodge();

	void Slash();

	void Run();
	void UnRun();

	void CrouchStart();
	void CrouchEnd();
};
