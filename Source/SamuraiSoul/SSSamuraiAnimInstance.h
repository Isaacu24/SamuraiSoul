// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SSSamuraiAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSSamuraiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USSSamuraiAnimInstance();

	void PlayDodgeMontage();
	void PlayEquipMontage();
	void PlayUnarmMontage();
	void PlayEquipRootMontage();
	void PlayUnarmRootMontage();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void AnimNotify_DodgeEnd();

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Speed = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Direction = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsCrouch = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsAir = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsEquip = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsLastEquip = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAnimMontage> UnarmMontage;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAnimMontage> EquipRootMontage;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UAnimMontage> UnarmRootMontage;
};
