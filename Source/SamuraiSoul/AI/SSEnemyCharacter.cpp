// Fill out your copyright notice in the Description page of Project Settings.


#include "SSEnemyCharacter.h"
#include "SSEnemyAnimInstance.h"
#include "../Abilities/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

ASSEnemyCharacter::ASSEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BODY_MESH(TEXT("/Script/Engine.SkeletalMesh'/Game/MyContent/Mesh/Enemy/Samurai/SK_EnemySamurai_Katana.SK_EnemySamurai_Katana'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SAMURAI(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContent/Animation/AI/AB_SSEnemyCharacter.AB_SSEnemyCharacter_C'"));

	if (true == BODY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BODY_MESH.Object);
	}

	if (true == ANIM_SAMURAI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_SAMURAI.Class);
	}

	GetMesh()->SetRelativeLocation(FVector{ 0.f, 0.f, -87.5f });
	GetMesh()->SetRelativeRotation(FRotator{ 0.f, -90.f, 0.f });
}

void ASSEnemyCharacter::DamageCheck()
{
	if (0.f >= Attributes->GetHealth())
	{
		return;
	}

	if (nullptr != AbilitySystemComponent
		&& nullptr != DamageEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			UE_LOG(LogTemp, Log, TEXT("Enemy HP: %f"), Attributes->GetHealth());

			//Hit Ability
			HitDelegate.Execute();

			if (0.f >= Attributes->GetHealth())
			{
				DeathDelegate.Execute();
			}
		}
	}
}
