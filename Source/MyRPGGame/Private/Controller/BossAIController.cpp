// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/BossAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyCharacter.h"

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(InPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("ActorSpawn"),InPawn->GetActorLocation());
	}
}

ABossAIController::ABossAIController()
{
}
