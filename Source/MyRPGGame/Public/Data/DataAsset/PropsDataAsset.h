// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UPropsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	//用于重写工具的产生效果
	virtual void TakeEffect();
	UFUNCTION(BlueprintCallable)
	virtual void LoseEffect();
	UPROPERTY(EditAnywhere)
	float AttackGain;
	UPROPERTY(EditAnywhere)
	float DefenceGain;
	UPROPERTY(EditAnywhere)
	float ManaGain;
	UPROPERTY(EditAnywhere)
	float LifeRegeneration;
	UPROPERTY(EditAnywhere)
	float DuraingTime;
};
