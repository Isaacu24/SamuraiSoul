// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSCombatComponent.h"
#include "Item/Weapon/SSWeapon.h"
#include "Item/Weapon/SSWeapon_Katana.h"

// Sets default values for this component's properties
USSCombatComponent::USSCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USSCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

//분기를 웨폰에 둔다. 무기의 타입에 따라 정하기
//void USSCombatComponent::AttackEvent()
//{
//}
//
//void USSCombatComponent::HitEvent()
//{
//	//switch(EAttckType)
//	//to do
//}


// Called every frame
void USSCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USSCombatComponent::EquipWeapon(USceneComponent* InParent, FName InSocketName)
{
	Weapon = GetWorld()->SpawnActor<ASSWeapon_Katana>();

	if (nullptr != Weapon)
	{
		Weapon->Equip(InParent, InSocketName);
		Weapon->SetOwner(GetOwner());
	}
}



