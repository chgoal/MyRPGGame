// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "SkinSocketUserWidget.generated.h"

class UImage;
class UTextBlock;
class UDescribeUserWidget;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API USkinSocketUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
public:
	ESkinType GetSkinType() const;
	void UpdateIcon(int32 ID);
	void Reload();
	bool InWitchBox(ESkinType SkinType);

	void UpdatePos();
	void RemoveDescribe();
protected:
	UPROPERTY()
	int32 SavedID = -1;
	UPROPERTY(EditAnywhere)
    ESkinType SkinType;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* SkinSign;
    UPROPERTY(meta=(BindWidget))
    UImage* SkinIcon;
	UPROPERTY(EditAnywhere)
	bool bSwitchBox;

	UPROPERTY()
	UDescribeUserWidget* DescribeWidget;
	FTimerHandle DescribeHandle;
};
