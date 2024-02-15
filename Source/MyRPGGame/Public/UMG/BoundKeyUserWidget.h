// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "BoundKeyUserWidget.generated.h"

class UTextBlock;
class UImage;
class UItemUserWidget;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBoundKeyUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	UPROPERTY(meta=(BindWidget))
	UImage* BoundIcon;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* BoundKey;
	UPROPERTY(EditAnywhere)
	FName BoundName;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EQuickUse QuickUse;
	UPROPERTY(EditAnywhere)
	FText Key;
	UPROPERTY()
	int32 SavedID;
public:
	void UpdateWidget(int32 Out_ID);
	EQuickUse GetQuickUse();
	UFUNCTION(BlueprintCallable)
	static FName ConvertQuickUseToName(EQuickUse T_QuickUse);
	UFUNCTION(BlueprintCallable)
	FText GetBoundKeyText();
};
