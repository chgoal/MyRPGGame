// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/BaseAIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API ABossAIController : public ABaseAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
public:
	ABossAIController();
};
