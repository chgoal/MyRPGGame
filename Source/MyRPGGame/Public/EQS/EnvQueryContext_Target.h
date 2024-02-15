// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvQueryContext_Target.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UEnvQueryContext_Target : public UEnvQueryContext
{
	GENERATED_BODY()
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
protected:
	UPROPERTY(EditAnywhere)
	FName SelectKeyName;
public:
	UEnvQueryContext_Target();
};
