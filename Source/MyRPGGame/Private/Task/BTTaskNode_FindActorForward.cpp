// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskNode_FindActorForward.h"
#include "Controller/BaseAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTaskNode_FindActorForward::UBTTaskNode_FindActorForward()
{
	NodeName = TEXT("物体前方");
	Origin.AddObjectFilter(this,TEXT("OriginActor"),AActor::StaticClass());
	Target.AddVectorFilter(this,TEXT("Target"));
}

void UBTTaskNode_FindActorForward::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBData = GetBlackboardAsset();
	if (BBData)
	{
		Origin.ResolveSelectedKey(*BBData);
		Target.ResolveSelectedKey(*BBData);
	}
}

EBTNodeResult::Type UBTTaskNode_FindActorForward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Origin.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	FVector OriginPos;
	FRotator OriginRot;
	FVector TargetPos;
	if (AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(Origin.GetSelectedKeyID())))
	{
		OriginPos = TargetActor->GetActorLocation();
		OriginRot = TargetActor->GetActorRotation();
		OriginPos = OriginPos+OriginRot.Vector()*Distance;
	}
	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(OwnerComp.GetAIOwner(),OriginPos,TargetPos,radius))
	{
		if (OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(Target.GetSelectedKeyID(),TargetPos))
		{
			
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
