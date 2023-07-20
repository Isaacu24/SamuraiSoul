// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SSGA_WolfDraw.h"
#include "SSGameplayTags.h"
#include "Character/SSWolf.h"
#include "GameFramework/Character.h"
#include "Interface/SSBehaviorInterface.h"

USSGA_WolfDraw::USSGA_WolfDraw()
{
	AbilityID = ESSAbilityID::WolfDraw;

	//AbilityTags.AddTag(FSSGameplayTags::Get().Ability_WolfDrawTag);
	//ActivationOwnedTags.AddTag(FSSGameplayTags::Get().Ability_WolfDrawTag);
	//BlockAbilitiesWithTag.AddTag(FSSGameplayTags::Get().AbilityTag);
}

void USSGA_WolfDraw::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MyCharacter = Cast<ACharacter>(ActorInfo->AvatarActor);
	check(MyCharacter);

	ISSBehaviorInterface* BehaviorPawn = Cast<ISSBehaviorInterface>(MyCharacter);

	if (nullptr != BehaviorPawn)
	{
		if (false == BehaviorPawn->IsEquip())
		{
			Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
	}

	PlayMontage(Montage, Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USSGA_WolfDraw::SpawnWolf, 1.25, false);
}

void USSGA_WolfDraw::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USSGA_WolfDraw::SpawnWolf()
{
	if (nullptr == MyCharacter)
	{
		return;
	}

	FTransform CharacterTransform = MyCharacter->GetActorTransform();

	SpawnedWolf = GetWorld()->SpawnActorDeferred<ASSWolf>(ProjectileClass, CharacterTransform, GetOwningActorFromActorInfo(),
	                                                      MyCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	SpawnedWolf->FinishSpawning(CharacterTransform);
	SpawnedWolf->RunWolf(MyCharacter);
}
