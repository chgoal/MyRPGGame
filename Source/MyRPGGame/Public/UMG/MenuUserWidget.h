// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

class UButton;
class UKeyUserWidget;
class UOverlay;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UOverlay* FellowUI;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Quit;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Set;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Screen;
	UPROPERTY()
	UKeyUserWidget* KeyUserWidget;
	UPROPERTY()
	UKeyUserWidget* SettingWidget;
	UPROPERTY(BlueprintReadOnly)
	UConfirmUserWidget* ConfirmUserWidget;

	virtual void NativeConstruct() override;
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
public:
	virtual void RemoveFromParent() override;
public:
	UFUNCTION()
	void OnClick_Quit();
	UFUNCTION()
	void OnClick_Set();
	UFUNCTION()
	void OnClick_Screen();
};
