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
	void PlaySlashMontage();

	void PlayEquipRootMontage();
	void PlayUnarmRootMontage();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void AnimNotify_DodgeEnd();
	
	UPROPERTY()
	TObjectPtr<class ASSSamuraiCharacter> MyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	float Direction = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	bool IsCrouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	bool IsAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	bool IsEquip = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> UnarmMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> EquipRootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> UnarmRootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> SlashMontage;
};
