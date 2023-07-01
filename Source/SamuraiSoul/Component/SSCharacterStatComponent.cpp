#include "Component/SSCharacterStatComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SSAttributeSet.h"
#include "SSGameplayTags.h"

USSCharacterStatComponent::USSCharacterStatComponent()
{
}

void USSCharacterStatComponent::SetAbilityDelegates()
{
	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetOwner());

	if (nullptr != AbilityPawn)
	{
		if (nullptr != AbilityPawn->GetAbilitySystemComponent())
		{
			OwnerAttributeSet = AbilityPawn->GetAbilitySystemComponent()->GetSet<USSAttributeSet>();

			//Reaction Ability binding
			OwnerAttributeSet->OnDefenseHitEvent.AddUObject(this, &ThisClass::HandleDefenseHit);
			OwnerAttributeSet->OnSubtractBPEvent.AddUObject(this, &ThisClass::HandleBPSubtracted);
			OwnerAttributeSet->OnReboundEvent.AddUObject(this, &ThisClass::HandleRebound);
			OwnerAttributeSet->OnBeExecutedEvent.AddUObject(this, &ThisClass::HandleBeExecuted);

			OwnerAttributeSet->OnDamagedEvent.AddUObject(this, &ThisClass::HandleDamaged);
			OwnerAttributeSet->OnDeadEvent.AddUObject(this, &ThisClass::HandleDead);
		}
	}
}

// Called when the game starts
void USSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USSCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USSCharacterStatComponent::SetHandleGameplayEvent(FGameplayTag Tag, AActor* DamageInstigator, AActor* DamageCauser,
                                                       const FGameplayEffectSpec& DamageEffectSpec,
                                                       float DamageMagnitude)
{
	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetOwner());

	if (nullptr != AbilityPawn)
	{
		FGameplayEventData Payload;
		Payload.EventTag       = Tag;
		Payload.Instigator     = DamageInstigator;
		Payload.Target         = AbilityPawn->GetAbilitySystemComponent()->GetAvatarActor();
		Payload.OptionalObject = DamageEffectSpec.Def;
		Payload.ContextHandle  = DamageEffectSpec.GetEffectContext();
		Payload.InstigatorTags = *DamageEffectSpec.CapturedSourceTags.GetAggregatedTags();
		Payload.TargetTags     = *DamageEffectSpec.CapturedTargetTags.GetAggregatedTags();
		Payload.EventMagnitude = DamageMagnitude;

		AbilityPawn->GetAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);

		return true;
	}

	return false;
}

void USSCharacterStatComponent::HandleDefenseHit(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
                                                 float DamageMagnitude)
{
	OnBPChanged.Broadcast(OwnerAttributeSet->GetBalance());
}

void USSCharacterStatComponent::HandleDamaged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
                                              float DamageMagnitude)
{
	bool IsSuccessed = SetHandleGameplayEvent(FSSGameplayTags::Get().HitTag, DamageInstigator, DamageCauser, DamageEffectSpec, DamageMagnitude);

	if (true == IsSuccessed)
	{
		OnHPChanged.Broadcast(OwnerAttributeSet->GetHealth());
	}
}

void USSCharacterStatComponent::HandleDead(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude)
{
	bool IsSuccessed = SetHandleGameplayEvent(FSSGameplayTags::Get().DeadTag, DamageInstigator, DamageCauser, DamageEffectSpec, DamageMagnitude);

	if (true == IsSuccessed)
	{
		OnHPChanged.Broadcast(OwnerAttributeSet->GetHealth());
	}

	OnHPZero.Broadcast();
}

void USSCharacterStatComponent::HandleBPSubtracted(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
                                                   float DamageMagnitude)
{
	if (0.f >= OwnerAttributeSet->GetBalance() - 0.01f)
	{
		GetWorld()->GetTimerManager().SetTimer(BPZeroHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (0.f >= OwnerAttributeSet->GetBalance() - 0.01f)
			{
				OnBPZero.Broadcast();
			}
		}), 5.0f, false);
	}

	OnBPChanged.Broadcast(OwnerAttributeSet->GetBalance());
}

void USSCharacterStatComponent::HandleBeExecuted(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
                                                 float DamageMagnitude)
{
	SetHandleGameplayEvent(FSSGameplayTags::Get().BeExecutedTag, DamageInstigator, DamageCauser, DamageEffectSpec, DamageMagnitude);
}

void USSCharacterStatComponent::HandleRebound(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
                                              float DamageMagnitude)
{
	SetHandleGameplayEvent(FSSGameplayTags::Get().ReboundTag, DamageInstigator, DamageCauser, DamageEffectSpec, DamageMagnitude);
}

float USSCharacterStatComponent::GetHealth() const
{
	if (nullptr == OwnerAttributeSet)
	{
		return 0.f;
	}

	return OwnerAttributeSet->GetHealth();
}

float USSCharacterStatComponent::GetMaxHealth() const
{
	if (nullptr == OwnerAttributeSet)
	{
		return 0.f;
	}

	return OwnerAttributeSet->GetMaxHealth();
}


float USSCharacterStatComponent::GetBalance() const
{
	if (nullptr == OwnerAttributeSet)
	{
		return 0.f;
	}

	return OwnerAttributeSet->GetBalance();
}

float USSCharacterStatComponent::GetMaxBalance() const
{
	if (nullptr == OwnerAttributeSet)
	{
		return 0.f;
	}

	return OwnerAttributeSet->GetMaxBalance();
}
