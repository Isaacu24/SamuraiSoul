// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "SSAbilitySystemComponent.h"
#include "SSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_FourParams(FSSAttributeEventDelegate,
                                      AActor* /*EffectInstigator*/,
                                      AActor* /*EffectCauser*/,
                                      const FGameplayEffectSpec& /*EffectSpec*/,
                                      float /*EffectMagnitude*/
                                     );

UCLASS()
class SAMURAISOUL_API USSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USSAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Balance)
	FGameplayAttributeData Balance;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Balance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxBalance)
	FGameplayAttributeData MaxBalance;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, MaxBalance);

	//Damage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Damage);

	//Rebound
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Rebound)
	FGameplayAttributeData Rebound;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Rebound);

	//BeExecuted
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_BeExecuted)
	FGameplayAttributeData BeExecuted;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, BeExecuted);

	//BeAssassinated
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_BeAssassinated)
	FGameplayAttributeData BeAssassinated;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, BeAssassinated);

	mutable FSSAttributeEventDelegate OnDefenseHitEvent;
	mutable FSSAttributeEventDelegate OnSubtractBPEvent;
	mutable FSSAttributeEventDelegate OnReboundEvent;
	mutable FSSAttributeEventDelegate OnBeExecutedEvent;
	mutable FSSAttributeEventDelegate OnBeAssassinatedEvent;

	mutable FSSAttributeEventDelegate OnDamagedEvent;
	mutable FSSAttributeEventDelegate OnDeadEvent;

	// 이펙트가 적용된 후에 자동으로 호출되는 함수
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// 속성이 변경된 후에 자동으로 호출되는 함수
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	//레플레이션 관련 함수들
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

	UFUNCTION()
	virtual void OnRep_Balance(const FGameplayAttributeData& OldBalance);

	UFUNCTION()
	virtual void OnRep_MaxBalance(const FGameplayAttributeData& OldMaxBalance);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);

	UFUNCTION()
	virtual void OnRep_Rebound(const FGameplayAttributeData& OldRebound);

	UFUNCTION()
	virtual void OnRep_BeExecuted(const FGameplayAttributeData& OldBeExecuted);

	UFUNCTION()
	virtual void OnRep_BeAssassinated(const FGameplayAttributeData& OldAssassinated);

private:
	void Down();

	FTimerHandle DownHandle;
};
