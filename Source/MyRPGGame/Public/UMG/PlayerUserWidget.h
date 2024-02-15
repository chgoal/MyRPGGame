// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUserWidget.generated.h"

class UHorizontalBox;
class UBoundKeyUserWidget;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UPlayerUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* BoundHorizon;
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	
public:
	virtual void RemoveFromParent() override;
	UFUNCTION()
	void BoundProps(EQuickUse Out_QuickUse,int32 Out_Site,int32 Out_ID) const;
	UFUNCTION()
	void UnBoundProps(EQuickUse Out_QuickUse,int32 Out_Site,int32 Out_ID) const;
	UFUNCTION()
	void UnBoundAllProps() const;
};


