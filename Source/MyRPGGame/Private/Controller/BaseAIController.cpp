// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/BaseAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyCharacter.h"
#include "MyRPGGame/MyRPGGame.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"

ABaseAIController::ABaseAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiComp"));
}


void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(InPawn))
	{
		if (EnemyCharacter->GetBehaviorTree())
		{
			RunBehaviorTree(EnemyCharacter->GetBehaviorTree());
			GetBlackboardComponent()->SetValueAsVector(TEXT("NextVecto"),InPawn->GetActorLocation()+InPawn->GetActorForwardVector()*100);
		}
	}
}

FGenericTeamId ABaseAIController::GetGenericTeamId() const
{
	if (TeamColor == ETeamColor::ETC_Green)
	{
		return TeamID_Green;
	}
	if (TeamColor == ETeamColor::ETC_Yellow)
	{
		return TeamID_Yellow;
	}
	return TeamID_Red;
}
