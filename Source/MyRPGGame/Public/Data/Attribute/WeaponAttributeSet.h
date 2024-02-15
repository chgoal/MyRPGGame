// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Attribute/BaseAttributeSet.h"
#include "WeaponAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UWeaponAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet,Endurance)
};
