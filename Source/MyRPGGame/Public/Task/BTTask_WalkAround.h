// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_WalkAround.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBTTask_WalkAround : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_WalkAround();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetPosition;//存储的点
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OriginPosition;//获得的点
	UPROPERTY(EditAnywhere)
	float MaxRadius;//当没有目标时寻找位置
	UPROPERTY(EditAnywhere)
	float MinRadius;//有目标时旋转走
	
};


