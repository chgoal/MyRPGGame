// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Subsystem/WeaponSubsystem.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category="BaseProps")
	//攻击力增加
	float Attack;
	UPROPERTY(EditAnywhere,Category="BaseProps")
	//防御力增加
	float Defence;
	UPROPERTY(EditAnywhere,Category="BaseProps|Gun")
	//最大子弹数
	float MaxBullet;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseProps|Gun")
	//当前子弹数
	float CurrentBullet;
	UPROPERTY(EditAnywhere,Category="BaseProps|Gun")
	//一组子弹数
	float GroupBullet;
	UPROPERTY(EditAnywhere,Category="BaseProps")
	bool bEquip;
	UFUNCTION(BlueprintCallable)
	FWeaponMsg GetWeaponMsg();
	// UFUNCTION(BlueprintCallable)
	// virtual void WeaponEffect(float rate = 0.f);
	
};
