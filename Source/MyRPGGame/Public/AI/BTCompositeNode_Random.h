// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTCompositeNode_Random.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBTCompositeNode_Random : public UBTCompositeNode
{
	GENERATED_BODY()
	virtual int32 GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
public:
	UBTCompositeNode_Random(const FObjectInitializer& ObjectInitializer);
};
