// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CustomButton.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCustomButtonHoverEvent,int32)
UCLASS()
class MYRPGGAME_API UCustomButton : public UButton
{
	GENERATED_BODY()
protected:
	
	UPROPERTY()
	FButtonStyle ButtonStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance", meta=( DisplayName="Select" ))
	bool bSelected;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Appearance", meta=( DisplayName="Serial" ))
	int32 Serial;//序列值，在加入时就需要设置
	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void PostLoad() override;
	void CustomSlateHandleHovered();
	void CustomSlateHandleUnhovered();
public:
	explicit UCustomButton(const FObjectInitializer& ObjectInitializer);
	void SetSelect(bool Out_Selected);
	void SetSerial(int32 Out_Serial);
	int32 GetSerial();

	FOnCustomButtonHoverEvent OnCustomButtonHover;
	FOnCustomButtonHoverEvent OnCustomButtonUnHover;
	
	
};


