// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveGameBarUserWidget.generated.h"

class UButton;
class UTextBlock;
class UMyRPGSaveGame;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API USaveGameBarUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY()
	UMyRPGSaveGame* MyRPGSaveGame;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SaveTime;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SaveMsg;
	UPROPERTY(meta=(BindWidget))
	UButton* SaveButton;

	FTimerHandle TimerHandle;
public:
	void UpdateSaveGameBar(UMyRPGSaveGame* RPGSaveGame);
	UFUNCTION()
	void OnDoubleClick();
	UFUNCTION()
	void LoadGame();
};
