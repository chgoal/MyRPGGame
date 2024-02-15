// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "PackageUserWidget.generated.h"
class UBoundKeyUserWidget;
class USkinSocketUserWidget;
DECLARE_MULTICAST_DELEGATE(NotifyScreenWidget)

class UCanvasPanel;
class UWeaponUserWidget;
class UVerticalBox;
class APlayerModel;
class ASceneItem;
class UScollerBoxUserWidget;
class UDescribeUserWidget;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UPackageUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	virtual void RemoveFromParent() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY(meta=(BindWidget))
	UScollerBoxUserWidget* NearItemScoller;
	UPROPERTY(meta=(BindWidget))
	UScollerBoxUserWidget* PackageItemScoller;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* SkinVerticalBox;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* PropsVerticalBox;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* WeaponSocket;
	UPROPERTY(EditAnywhere)
	APlayerModel* PlayerModel;

public:
	UFUNCTION()
	void OnNearItemEnter(ASceneItem* SceneItem) const;
	UFUNCTION()
	void OnNearItemLeave(ASceneItem* SceneItem) const;
	UFUNCTION()
	void OnAddItemToPackage(int32 Site,FIDAndType IDAndType) const;
	UFUNCTION()
	void OnRemoveItemFromPackage(int32 Site,FIDAndType IDAndType) const;
	UFUNCTION()
	void PutinSkin(ESkinType SkinType,int32 ID);
	UFUNCTION()
	void TakeOffSkin(ESkinType SkinType,int32 ID);
	UFUNCTION()
	USkinSocketUserWidget* FindWidgetFromType(ESkinType SkinType);
	UFUNCTION()
	UBoundKeyUserWidget* FindWidgetFromQuickUse(EQuickUse QuickUse);
	UFUNCTION()
	void AddWeaponToPackage(int32 Site,FWeaponMsg WeaponMsg);
	UFUNCTION()
	void RemoveWeaponFromPackage(int32 Site,FWeaponMsg WeaponMsg);
	UFUNCTION()
	void ExChangeWeapon(int32 Site1,int32 Site2);
	UFUNCTION()
	void BoundProps(EQuickUse Out_QuickUse,int32 Out_Site,int32 Out_ID);
	UFUNCTION()
	void UnBoundProps(EQuickUse Out_QuickUse,int32 Out_Site,int32 Out_ID);
	UFUNCTION()
	void ReloadWeaponWidget();
	UFUNCTION()
	void ReloadSkinWidget();
	UFUNCTION()
	void ReloadPropsWidget();
	
	NotifyScreenWidget OnScreenWidgetClose;

};


