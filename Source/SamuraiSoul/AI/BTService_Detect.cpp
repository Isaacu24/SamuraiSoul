// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Detect.h"
#include "AIController.h"
#include "Interface/SSCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
	{
		return;
	}

	const FVector Center = ControllingPawn->GetActorLocation();
	const UWorld* World  = ControllingPawn->GetWorld();

	if (nullptr == World)
	{
		return;
	}

	ISSCharacterAIInterface* AIPawn = Cast<ISSCharacterAIInterface>(ControllingPawn);

	if (nullptr == AIPawn)
	{
		return;
	}

	float DetectRadius = AIPawn->GetAIDetectRange();

	TArray<FOverlapResult> OverlapResults = {};
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);

	bool bResult = World->OverlapMultiByChannel(
	                                            OverlapResults,
	                                            Center,
	                                            FQuat::Identity,
	                                            ECollisionChannel::ECC_EngineTraceChannel2,
	                                            FCollisionShape::MakeSphere(DetectRadius),
	                                            CollisionQueryParam
	                                           );


	if (true == bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());

			if (nullptr != Pawn
				&& true == Pawn->GetController()->IsPlayerController())
			{
				FVector A = ControllingPawn->GetActorForwardVector();
				FVector B = A - Pawn->GetActorLocation();

				A.Normalize();
				B.Normalize();

				if (false == CheckSight(A, B, AIPawn->GetAISight()))
				{
					return;
				}

				const float DistanceToTarget = ControllingPawn->GetDistanceTo(Pawn);

				if (200.f <= DistanceToTarget)
				{
					AIPawn->Run();
				}

				else
				{
					AIPawn->Walk();
				}

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.1f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.17f);

				return;
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), nullptr);
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}
}

bool UBTService_Detect::CheckSight(const FVector& A, const FVector& B, float Sight)
{
	float ReturnValue = FVector::DotProduct(A, B);

	float angle = FMath::Cos(Sight / 2);

	GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Blue, FString::SanitizeFloat(angle));

	if (angle <= ReturnValue)
	{
		return false;
	}

	return true;
}
