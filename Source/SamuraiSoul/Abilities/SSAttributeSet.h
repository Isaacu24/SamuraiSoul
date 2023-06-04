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

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, AttackPower);

	//Damage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Damage);

	mutable FSSAttributeEventDelegate OnDamagedEvent;
	mutable FSSAttributeEventDelegate OnDeadEvent;

	// ����Ʈ�� ����� �Ŀ� �ڵ����� ȣ��Ǵ� �Լ�
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// �Ӽ��� ����� �Ŀ� �ڵ����� ȣ��Ǵ� �Լ�
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	//���÷��̼� ���� �Լ���
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
};
