// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetBool.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBTTaskNode_SetBool : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_SetBool();
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetBool;
	UPROPERTY(EditAnywhere)
	bool NewBool;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
};
