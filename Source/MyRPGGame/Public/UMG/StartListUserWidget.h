// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartListUserWidget.generated.h"


class UCustomButton;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UStartListUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SelectChange(int32 Delta);
	int32 GetSelectButton();
	void SelectKeyClick();
protected:
	UPROPERTY()
	int32 SelectButton;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* ButtonVertical;
	UPROPERTY(BlueprintReadOnly)
	int32 MaxButton;
	UPROPERTY(meta=(BindWidget))
	UCustomButton* ContinueGame;
	
	void OnHovered(int32 Serial);
	void OnUnHovered(int32 Serial);
	
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;

	UFUNCTION()
	void OnClick_ContinueGame();
	
	
};

