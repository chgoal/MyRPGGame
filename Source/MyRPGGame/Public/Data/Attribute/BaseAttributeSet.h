// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,AttackPower)
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData DefencePower;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,DefencePower)
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,MoveSpeed)
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData JumpSpeed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet,JumpSpeed)


	
	
};
