// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SamuraiSoul.h"
#include "Components/ActorComponent.h"
#include "SSCombatComponent.generated.h"

class ASSWeapon;
class USceneComponent;

DECLARE_DELEGATE_OneParam(FCombatDelegate, EWeaponType Type);
DECLARE_DELEGATE(FExecuteDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMURAISOUL_API USSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USSCombatComponent();

	FCombatDelegate AttackEvent;
	FCombatDelegate HitEvent;
	FExecuteDelegate ExecutionEvent;
	FExecuteDelegate ExecutedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASSWeapon> DefenseBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ExecutionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ExecutedMontage;

	void OnExecutionEvent();
	void OnExecutedEvent();

	void OnDefense();
	void OffDefense();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipWeapon(USceneComponent* InParent, FName InSocketName);
	void EquipDefenseBarrier();
};
