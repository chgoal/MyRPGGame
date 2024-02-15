// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadSaveUserWidget.generated.h"

class UVerticalBox;
class UMyRPGSaveGame;
class USaveGameBarUserWidget;
class UButton;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API ULoadSaveUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_SaveGame;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* SaveGameList;
	UPROPERTY()
	UMyRPGSaveGame* SaveGameInstance;
	
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	virtual void NativeConstruct() override;

	
public:
	UFUNCTION()
	void SaveGameOnClick();
	UFUNCTION()
	void UpdateSaveGameBar();
	virtual void RemoveFromParent() override;
};
