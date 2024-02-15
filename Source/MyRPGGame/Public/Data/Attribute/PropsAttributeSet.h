// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Attribute/BaseAttributeSet.h"
#include "PropsAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UPropsAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData HealthRecover;//生命恢复
	ATTRIBUTE_ACCESSORS(UPropsAttributeSet,HealthRecover)
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData ManaRecover;//魔法恢复
	ATTRIBUTE_ACCESSORS(UPropsAttributeSet,ManaRecover)
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData StaminaRecover;//体力恢复
	ATTRIBUTE_ACCESSORS(UPropsAttributeSet,StaminaRecover)
	
};
