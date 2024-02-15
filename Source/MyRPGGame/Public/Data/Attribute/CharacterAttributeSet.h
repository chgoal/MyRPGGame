// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Attribute/BaseAttributeSet.h"
#include "CharacterAttributeSet.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class MYRPGGAME_API UCharacterAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
public:
	UCharacterAttributeSet();
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,Health);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,MaxHealth);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,Mana);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,MaxMana);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)//体力
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,Stamina);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet,MaxStamina);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};


