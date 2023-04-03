// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "SSAbilitySystemComponent.h"
#include "SSAttributeSet.generated.h"

//getter와 setter 함수를 자동으로 생성해주는 매크로
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class SAMURAISOUL_API USSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	USSAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USSAttributeSet, AttackPower);

	// 이펙트가 적용된 후에 자동으로 호출되는 함수
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// 속성이 변경된 후에 자동으로 호출되는 함수
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


	//레플레이션 관련 함수들
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
};
