// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPoint.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBTTask_FindPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindPoint();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetPosition;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OriginPosition;
	UPROPERTY(EditAnywhere)
	float radius;
};
