// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetInt.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBTTaskNode_SetInt : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_SetInt();
protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	int32 Out_Num;
	UPROPERTY(EditAnywhere)
	int32 Add_Num;
	UPROPERTY(EditAnywhere)
	int32 CycleNum;
	UPROPERTY(EditAnywhere)
	bool bAddModel;
	UPROPERTY(EditAnywhere)
	bool bCycle;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelectorKey;
};


