// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindActorForward.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBTTaskNode_FindActorForward : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_FindActorForward();
protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	float Distance;
	UPROPERTY(EditAnywhere)
	float radius;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Origin;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;
};
