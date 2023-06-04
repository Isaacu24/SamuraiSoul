#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "SSEnemyCharacter.generated.h"

class USSUserWidget;

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

	virtual void SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	virtual void Run() override;
	virtual void Walk() override;

	virtual void SetupCharacterWidget(USSUserWidget* InUserWidget) override;

	virtual void SetHiddenHPBar(bool Value) const override;
	virtual void SetHiddenTargetCursor(bool Value) const override;

	virtual void Die() const override;
};
