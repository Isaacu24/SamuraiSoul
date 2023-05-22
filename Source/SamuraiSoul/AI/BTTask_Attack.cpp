// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "Interface/SSCharacterAIInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	const auto TargetObject   = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));
	const AActor* TargetActor = Cast<AActor>(TargetObject);

	if (nullptr == TargetActor)
	{
		return EBTNodeResult::Failed;
	}

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetActor->GetActorLocation());
	Rotation.Pitch    = 0.f;
	ControllingPawn->SetActorRotation(Rotation);

	FAICharacterAbilityFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
	                            [&]()
	                            {
		                            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	                            });

	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->AttackByAI();

	return EBTNodeResult::InProgress;
}
