#pragma once

#include "CoreMinimal.h"
#include "SSEnemyCharacterBase.h"
#include "Game/SamuraiSoul.h"
#include "SSEnemyCharacter.generated.h"

class UGameplayEffect;

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
	virtual void Tick(float DeltaTime) override;

	virtual void SetAIAttackDelegate(const FAICharacterAbilityFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	virtual void RunBehaviorTree() const override;
	virtual void StopBehaviorTree() const override;

private:
};
