// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

USSAttributeSet::USSAttributeSet()
{
}

void USSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute InAttribute = Data.EvaluatedData.Attribute;

	if (Data.EvaluatedData.Attribute == GetDamageAttribute() && Data.EvaluatedData.Magnitude > 0.0f)
	{
		//Calculrate Damage.
		/*float NewHealth = FMath::Clamp(GetHealth() - GetDamage(), 0.0f, GetMaxHealth());
		SetHealth(NewHealth);
		SetDamage(0.0f);*/

		if (GetHealth() <= 0.0f)
		{
			//Dead
			//if (true == OnOutOfHealthDelegate.IsBound())
			//{
			//	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
			//	AActor* Instigator                                = EffectContext.GetOriginalInstigator();
			//	AActor* Causer                                    = EffectContext.GetEffectCauser();

			//	OnOutOfHealthDelegate.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
			//}
		}

		else
		{
			//Hit
			if (true == OnDamagedEvent.IsBound())
			{
				const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
				AActor* Instigator                                = EffectContext.GetOriginalInstigator();
				AActor* Causer                                    = EffectContext.GetEffectCauser();

				OnDamagedEvent.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
			}
		}
	}
}

void USSAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void USSAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USSAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USSAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USSAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
}

void USSAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, Health, OldHealth);
}

void USSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, MaxHealth, OldMaxHealth);
}

void USSAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, AttackPower, OldAttackPower);
}
