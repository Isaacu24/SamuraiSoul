// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SSCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHP*/);

class USSAttributeSet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAMURAISOUL_API USSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USSCharacterStatComponent();

	FORCEINLINE void SetAttributeSet(USSAttributeSet* AttributeSet)
	{
		OwnerAttributeSet = AttributeSet;
	}

public:
	FOnHPChangedDelegate OnHPChanged;

	float GetHealth() const;
	float GetMaxHealth() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<USSAttributeSet> OwnerAttributeSet;
};
