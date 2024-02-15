// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API UDeathUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayWidgetAnimation();
};
