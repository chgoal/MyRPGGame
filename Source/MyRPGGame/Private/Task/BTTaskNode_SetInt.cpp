// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskNode_SetInt.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"

UBTTaskNode_SetInt::UBTTaskNode_SetInt()
{
	NodeName = TEXT("增加int的值");
	Add_Num = 0;
	CycleNum = 1;
	SelectorKey.AddIntFilter(this,TEXT("OutNum"));
	bAddModel = false;
}

void UBTTaskNode_SetInt::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBData = GetBlackboardAsset();
	if (BBData)
	{
		SelectorKey.ResolveSelectedKey(*BBData);
	}
}
EBTNodeResult::Type UBTTaskNode_SetInt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (SelectorKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	if (!bAddModel)
	{
		if (OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Int>(SelectorKey.GetSelectedKeyID(),Out_Num))
        {
        	return EBTNodeResult::Succeeded;
        }
	}
	else
	{
		Out_Num = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(SelectorKey.GetSelectedKeyID());
		int32 TargetNum = Out_Num+Add_Num;
		if (bCycle && CycleNum !=0 )
		{
			TargetNum = TargetNum % CycleNum;
		}
		if (OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Int>(SelectorKey.GetSelectedKeyID(),TargetNum))
		{
			return EBTNodeResult::Succeeded;
		}
		
	}
	
	return EBTNodeResult::Failed;
}