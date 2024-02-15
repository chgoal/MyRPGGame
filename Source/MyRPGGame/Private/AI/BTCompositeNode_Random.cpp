// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTCompositeNode_Random.h"

int32 UBTCompositeNode_Random::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild,
	EBTNodeResult::Type LastResult) const
{
	int32 NextChildIndex = BTSpecialChild::ReturnToParent;
	if (PrevChild == BTSpecialChild::NotInitialized)//是否第一次进入子此节点
	{
		NextChildIndex = FMath::RandRange(0,GetChildrenNum());//获得子类的值
	}
	return NextChildIndex;
}

UBTCompositeNode_Random::UBTCompositeNode_Random(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Random";
}
