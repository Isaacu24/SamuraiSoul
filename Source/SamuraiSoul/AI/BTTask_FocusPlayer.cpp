// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FocusPlayer.h"
#include "SSEnemyBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SSAI.h"

UBTTask_FocusPlayer::UBTTask_FocusPlayer()
{
	NodeName = TEXT("Focus Player");
}

EBTNodeResult::Type UBTTask_FocusPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASSEnemyBaseAIController* Controller = Cast<ASSEnemyBaseAIController>(OwnerComp.GetOwner());
	UObject* TargetObject                = Controller->GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET);
	AActor* PlayerActor                  = Cast<AActor>(TargetObject);

	Controller->SetFocus(PlayerActor);

	return EBTNodeResult::Succeeded;
}
