// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuUserWidget.generated.h"

class ULoginUserWidget;
class UStartListUserWidget;
class UOverlay;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UStartMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UStartMenuUserWidget(const FObjectInitializer& ObjectInitializer);
protected:
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;//实现按键事件
	
	UPROPERTY(meta=(BindWidget))
	UOverlay* NextWidget;
	UPROPERTY()
	UStartListUserWidget* ListUserWidget;
	UPROPERTY()
	ULoginUserWidget* LoginUserWidget;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveY;
};
