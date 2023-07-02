#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "SSEnemyCharacter.generated.h"

class USSUserWidget;
class UBoxComponent;
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

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Die() override;

	virtual void SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;
	virtual void SpectialAttackByAI(const FGameplayTag& Tag) override;

	virtual void EquipUnarm() override;

	virtual void Run() override;
	virtual void Walk() override;

	virtual void VisibleTargetUI() override;
	virtual void HideTargetUI() override;

	virtual void SetupCharacterWidget(USSUserWidget* InUserWidget) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USSWidgetComponent> EnemyHUD;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> AssassinationCollider;
};
