// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescribeUserWidget.generated.h"

enum class EItemType : uint8;
/**
 * 
 */
class UTextBlock;
class UImage;
UCLASS()
class MYRPGGAME_API UDescribeUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DescribeText;
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	UPROPERTY()
	EItemType MItem;
	UPROPERTY()
	int32 MID;
public:
	void SetDescribeID(EItemType Item,int32 ID);
	void ClearDescribeID();
};
