// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/BaseCharacter.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
protected:
	UPROPERTY(EditAnywhere)
	ETeamColor TeamColor;
	
};
