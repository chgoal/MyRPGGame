// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskNode_SetBool.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

UBTTaskNode_SetBool::UBTTaskNode_SetBool()
{
	NodeName = TEXT("设置bool值");
	TargetBool.AddBoolFilter(this,TEXT("SelectBool"));
}

EBTNodeResult::Type UBTTaskNode_SetBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (TargetBool.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	if (OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(TargetBool.GetSelectedKeyID(),NewBool))
	{
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTaskNode_SetBool::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBData = GetBlackboardAsset();
	if (BBData)
	{
		TargetBool.ResolveSelectedKey(*BBData);
	}
}

