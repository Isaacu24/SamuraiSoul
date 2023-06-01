#include "Component/SSCharacterStatComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SSAttributeSet.h"
#include "SSGameplayTags.h"

USSCharacterStatComponent::USSCharacterStatComponent()
{
}

// Called when the game starts
void USSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	//IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetOwner());

	//if (nullptr != AbilityPawn)
	//{
	//	if (nullptr != AbilityPawn->GetAbilitySystemComponent())
	//	{
	//		//OwnerAttributeSet = AbilityPawn->GetAbilitySystemComponent()->GetAttributeSet();
	//		//OwnerAttributeSet->OnDamagedEvent.AddUObject(this, &ThisClass::HandleDamaged);
	//	}
	//}
}

void USSCharacterStatComponent::HandleDamaged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec,
                                              float DamageMagnitude)
{
	IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(GetOwner());

	if (nullptr != AbilityPawn)
	{
		FGameplayEventData Payload;
		Payload.EventTag       = FSSGameplayTags::Get().HitTag;
		Payload.Instigator     = DamageInstigator;
		Payload.Target         = AbilityPawn->GetAbilitySystemComponent()->GetAvatarActor();
		Payload.OptionalObject = DamageEffectSpec.Def;
		Payload.ContextHandle  = DamageEffectSpec.GetEffectContext();
		Payload.InstigatorTags = *DamageEffectSpec.CapturedSourceTags.GetAggregatedTags();
		Payload.TargetTags     = *DamageEffectSpec.CapturedTargetTags.GetAggregatedTags();
		Payload.EventMagnitude = DamageMagnitude;

		FScopedPredictionWindow NewScopedWindow(AbilityPawn->GetAbilitySystemComponent(), true);
		AbilityPawn->GetAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
	}
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
