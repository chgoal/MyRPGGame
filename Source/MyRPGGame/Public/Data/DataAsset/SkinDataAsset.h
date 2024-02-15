// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkinDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API USkinDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttbute")
	//防御
	int32 Defence;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttbute")
	//增加移动速度
	float AddWalkSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttbute")
	//增加跳跃时的速度
	float AddJumpHeight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseAttbute")
	//耐久度
	int32 NumberOfUse;
	
};
