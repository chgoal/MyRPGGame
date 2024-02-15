// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "QuickUseUserWidget.generated.h"

class UItemUserWidget;
class UDescribeUserWidget;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UQuickUseUserWidget : public UUserWidget
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
	EPropsType GetPropsType() const;
	void SetPropsType(int32 Out_ID);
	void UpdateIcon(int32 ID);
	void UpdateMessage(int32 Out_ID,int32 Out_Site);
	bool InWitchBox(EQuickUse QuickUse);
	int32 GetLinkedSite();
	EQuickUse GetQuickUse();
	void SetLinkedSite(int32 Out_Site);
	UItemUserWidget* GetItemUserWidget();

	void UpdatePos();
	void RemoveDescribe();
	void Reload();
	
protected:
	UPROPERTY()
	UItemUserWidget* ItemUserWidget;
	UPROPERTY()
	int32 SavedID = -1;
	UPROPERTY()
	int32 LinkedSite = -1;
	UPROPERTY(EditAnywhere)
	EQuickUse QuickUse;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PropsSign;
	UPROPERTY(meta=(BindWidget))
	UImage* PropsIcon;
	UPROPERTY()
	UDescribeUserWidget* DescribeUserWidget;
	
	FTimerHandle DescribeHandle;
};

inline UItemUserWidget* UQuickUseUserWidget::GetItemUserWidget()
{
	return ItemUserWidget;
}

inline void UQuickUseUserWidget::SetPropsType(int32 Out_ID)
{
	SavedID = Out_ID;
}
