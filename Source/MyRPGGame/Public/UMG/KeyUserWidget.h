// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyUserWidget.generated.h"

class UConfirmUserWidget;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UKeyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
};
