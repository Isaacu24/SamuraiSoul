// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Interface/SSBehaviorInterface.h"

USSAttributeSet::USSAttributeSet()
{
}

void USSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute InAttribute = Data.EvaluatedData.Attribute;

	if (InAttribute == GetDamageAttribute() && Data.EvaluatedData.Magnitude > 0.0f)
	{
		//Calculrate Damage.
		const float NewHealth = FMath::Clamp(GetHealth() - GetDamage(), 0.0f, GetMaxHealth());

		SetHealth(NewHealth);
		SetDamage(0.0f);

		if (GetHealth() <= 0.0f)
		{
			//Dead
			if (true == OnDeadEvent.IsBound())
			{
				const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
				AActor* Instigator                                = EffectContext.GetOriginalInstigator();
				AActor* Causer                                    = EffectContext.GetEffectCauser();

				OnDeadEvent.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
			}
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

	else if (InAttribute == GetReboundAttribute())
	{
		if (true == OnReboundEvent.IsBound())
		{
			const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
			AActor* Instigator                                = EffectContext.GetOriginalInstigator();
			AActor* Causer                                    = EffectContext.GetEffectCauser();

			OnReboundEvent.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
		}
	}

	else if (InAttribute == GetBeExecutedAttribute())
	{
		SetHealth(0.f);

		if (true == OnBeExecutedEvent.IsBound())
		{
			const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
			AActor* Instigator                                = EffectContext.GetOriginalInstigator();
			AActor* Causer                                    = EffectContext.GetEffectCauser();

			OnBeExecutedEvent.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
		}
	}

	else if (InAttribute == GetBeAssassinatedAttribute())
	{
		SetHealth(0.f);

		if (true == OnBeAssassinatedEvent.IsBound())
		{
			const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
			AActor* Instigator                                = EffectContext.GetOriginalInstigator();
			AActor* Causer                                    = EffectContext.GetEffectCauser();

			OnBeAssassinatedEvent.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
		}
	}

	else if (InAttribute == GetBalanceAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("BP: %f"), GetBalance());

		ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(GetOwningActor());

		if (nullptr == BehaviorPawn
			|| true == BehaviorPawn->IsDown())
		{
			return;
		}

		const float NewBalance = FMath::Clamp(GetBalance(), 0.0f, GetMaxBalance());
		SetBalance(NewBalance);

		if (GetMaxBalance() <= NewBalance)
		{
			Down();
		}

		if (0.f >= GetBalance() - 0.001f)
		{
			return;
		}

		if (true == OnSubtractBPEvent.IsBound())
		{
			const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
			AActor* Instigator                                = EffectContext.GetOriginalInstigator();
			AActor* Causer                                    = EffectContext.GetEffectCauser();

			OnSubtractBPEvent.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
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

void USSAttributeSet::OnRep_Balance(const FGameplayAttributeData& OldBalance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, Balance, OldBalance);
}

void USSAttributeSet::OnRep_MaxBalance(const FGameplayAttributeData& OldMaxBalance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, MaxBalance, OldMaxBalance);
}

void USSAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, Damage, OldDamage);
}

void USSAttributeSet::OnRep_Rebound(const FGameplayAttributeData& OldRebound)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, Rebound, OldRebound);
}

void USSAttributeSet::OnRep_BeExecuted(const FGameplayAttributeData& OldBeExecuted)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, BeExecuted, OldBeExecuted);
}

void USSAttributeSet::OnRep_BeAssassinated(const FGameplayAttributeData& OldAssassinated)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet, BeAssassinated, OldAssassinated);
}

void USSAttributeSet::Down()
{
	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(GetOwningActor());

	if (nullptr != BehaviorPawn)
	{
		BehaviorPawn->SetIsDown(true);

		GetWorld()->GetTimerManager().SetTimer(DownHandle, FTimerDelegate::CreateLambda([&]()
		{
			ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(GetOwningActor());
			BehaviorPawn->SetIsDown(false);
			SetBalance(GetMaxBalance() - 0.001f);
		}), 5.0f, false);
	}
}
