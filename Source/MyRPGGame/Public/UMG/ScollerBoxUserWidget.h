// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "ScollerBoxUserWidget.generated.h"

class UPackageUserWidget;
class ASceneItem;
class UItemUserWidget;
class UScrollBox;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UScollerBoxUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//功能型函数
	//控制背包外的加入和取出
	void AddItemUserWidget(ASceneItem* SceneItem) const;
	void RemoveItemUserWidget(ASceneItem* SceneItem) const;

	//控制背包内的加入和取出
	void AddItemUserWidget(int32 Site,FIDAndType IDAndType);
	void RemoveItemUserWidget(int32 Site);

	//根据Site查找ItemWidget
	UItemUserWidget* FindWidgetFromSite(int32 Site);

	//清空
	void ClearAll() const;
	void ResetAll() const;
	void DeleteAll() const;

	//在背包中重新加载
	void Reload();

	//获取和设置
	void SetPackageWidget(UPackageUserWidget* Out_PackageWidget);
protected:
	//继承
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	//一些绑定组件
	UPROPERTY(meta=(BindWidget))
	UScrollBox* ItemScoller;
	UPROPERTY(EditAnywhere)
	uint8 bPackageScrollBox;//用于确定是否是在Package当中，加入时需要将这个属性设置给对应的Item
	//变量
	UPROPERTY()
	TMap<int32,UItemUserWidget*> ScollerChild;
	UPROPERTY()
	UPackageUserWidget* PackageWidget;
};
