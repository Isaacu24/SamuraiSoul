#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "SSEnemyCharacter.generated.h"

class USSUserWidget;
class UBoxComponent;
class USSEnemyCombatComponent;
class AEnemyAssassinationEventTrigger;

DECLARE_DELEGATE(FAnimDelegate);

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API ASSEnemyCharacter : public ASSEnemyCharacterBase
{
	GENERATED_BODY()

public:
	ASSEnemyCharacter();

	virtual USSCombatComponent* GetCombatComponent() const override
	{
		return static_cast<USSCombatComponent*>(CombatComponent);
	}

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Die() override;

	virtual void AttackByAI() override;
	virtual void EquipUnarmByAI() override;

	virtual void DefenseByAI() override;

	virtual void SetParry(bool Value) override;
	virtual void SetHit(bool Value) override;
	virtual void SetDead(bool Value) override;
	virtual void SetRebound(bool Value) override;
	virtual void SetEquip(bool Value) override;
	virtual void SetBeExecuted(bool Value) override;

	virtual void Run() override;
	virtual void Walk() override;

	virtual void VisibleTargetUI() override;
	virtual void HideTargetUI() override;

	virtual void SetupCharacterWidget(USSUserWidget* InUserWidget) override;

	virtual EAttackType GetWeaponAttakType() const override;
	virtual void SetWeaponAttackType(EAttackType InType) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSEnemyCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSWidgetComponent> EnemyHUD;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> AssassinationCollider;

	UPROPERTY()
	uint8 CurrentNormalAttackCount;
};
