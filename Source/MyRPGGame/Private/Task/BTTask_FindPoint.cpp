// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_FindPoint.h"
#include "NavigationSystem.h"
#include "Controller/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_FindPoint::UBTTask_FindPoint()
{
	NodeName = TEXT("FindPoint");
	OriginPosition.AddObjectFilter(this,TEXT("OriginPosition"),AActor::StaticClass());
	OriginPosition.AddVectorFilter(this,TEXT("OriginPosition"));
	TargetPosition.AddVectorFilter(this,TEXT("TargetPosition"));
	radius = 0.f;
}

EBTNodeResult::Type UBTTask_FindPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OriginPosition.IsNone() || TargetPosition.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	FVector OriginPos;
	FVector TargetPos;
	if (OriginPosition.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		OriginPos = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(OriginPosition.GetSelectedKeyID());
	}
	else
	{
		if (AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OriginPosition.GetSelectedKeyID())))
		{
			OriginPos = TargetActor->GetActorLocation();
		}
	}
	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(OwnerComp.GetAIOwner(),OriginPos,TargetPos,radius))
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(TargetPosition.GetSelectedKeyID(),TargetPos);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_FindPoint::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBData = GetBlackboardAsset();
	if (BBData)
	{
		TargetPosition.ResolveSelectedKey(*BBData);
		OriginPosition.ResolveSelectedKey(*BBData);
	}
}
