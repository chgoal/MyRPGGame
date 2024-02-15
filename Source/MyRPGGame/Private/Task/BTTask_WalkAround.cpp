// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_WalkAround.h"

#include "NavigationSystem.h"
#include "Controller/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_WalkAround::UBTTask_WalkAround()
{
	NodeName = TEXT("FindAroundPoint");
	OriginPosition.AddObjectFilter(this,TEXT("OriginPosition"),AActor::StaticClass());
	OriginPosition.AddVectorFilter(this,TEXT("OriginPosition"));
	TargetPosition.AddVectorFilter(this,TEXT("TargetPosition"));
	MaxRadius = 0.f;
	MinRadius = 0.f;
}

EBTNodeResult::Type UBTTask_WalkAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OriginPosition.IsNone() || TargetPosition.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	if (MinRadius<0 || MaxRadius<0)
	{
		return EBTNodeResult::Failed;
	}
	FVector OriginPos;
	FVector TargetPos;
	int32 MaxCyc = 0;
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

	while (MaxCyc < 20)
	{
		if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(OwnerComp.GetAIOwner(),OriginPos,TargetPos,MaxRadius))
		{
			if (TargetPos.Size()>MinRadius)
			{
				break;
			}
		}
		MaxCyc = MaxCyc+1;
	}
	if (OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(TargetPosition.GetSelectedKeyID(),TargetPos))
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
void UBTTask_WalkAround::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBData = GetBlackboardAsset();
	if (BBData)
	{
		TargetPosition.ResolveSelectedKey(*BBData);
		OriginPosition.ResolveSelectedKey(*BBData);
	}
}