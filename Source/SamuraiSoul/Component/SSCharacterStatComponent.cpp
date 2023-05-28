#include "Component/SSCharacterStatComponent.h"
#include "Abilities/SSAttributeSet.h"

USSCharacterStatComponent::USSCharacterStatComponent()
{
}

// Called when the game starts
void USSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
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

void USSCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
