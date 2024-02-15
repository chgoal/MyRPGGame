// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "ItemUserWidget.generated.h"

class UVerticalBox;
class UUseUserWidget;
class UBorder;
class UDescribeUserWidget;
class ASceneItem;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UItemUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	//鼠标拖拽事件
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
public:
	virtual void RemoveFromParent() override;
	void ResetPanel();
	
	void InitPanel(int32 Site,FIDAndType ID);
	void InitPanel(ASceneItem* SceneItem);
	
	bool GetInPackage();
	EItemType GetItemType();
	int32 GetNumber();
	ASceneItem* GetSceneItem();
	int32 GetItemSite();
	void AddNumber(int32 Add_Number);

	//void OnClick();

	//设置类型
	void SetInPackage(bool Out_InPackage);
	void UpdatePos();
	void RemoveDescribe();
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Num;
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	UPROPERTY(meta=(BindWidget))
	UBorder* BackGround;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* ItemVertical;
	UPROPERTY()
	int32 ItemSite;//记录在列表中的位置
	UPROPERTY()
	//是否在背包中，主要用于打开使用面板
	bool bInPackage;
	UPROPERTY()
	//种类
	EItemType Item;
	UPROPERTY()
	int32 ID;
	UPROPERTY()
	//数量
	int32 Number;
	UPROPERTY()
	ASceneItem* ISceneItem;
	UPROPERTY()
	UDescribeUserWidget* DescribeWidget;
	UPROPERTY()
	UUseUserWidget* UseWidget;
	FTimerHandle DescribeHandle;
};
