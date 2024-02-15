// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UseUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UUseUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	UFUNCTION()
	void OnClick_Yes();
	UFUNCTION()
	void OnClick_No();
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Yes;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_No;
	int32 ID;
	int32 Site;
public:
	void InitWidget(int32 Out_ID,int32 Out_Site);
};
