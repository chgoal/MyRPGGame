// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/WeaponSubsystem.h"
#include "WeaponUserWidget.generated.h"

class UDescribeUserWidget;
struct FWeaponMsg;
class UImage;
class AWeapon;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UWeaponUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	int32 Site;
	UPROPERTY()
	AWeapon* Weapon;
	UPROPERTY(EditAnywhere)
	int32 TotalBullet;//总耐久
	UPROPERTY(EditAnywhere)
	int32 CurrentBullet;//现在的耐久
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponSite;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponRemain;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponGroup;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponMax;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponCurrent;
	UPROPERTY(meta=(BindWidget))
	UImage* WeaponIcon;
	UPROPERTY()
	FWeaponMsg WeaponMsg;
	UPROPERTY()
	UDescribeUserWidget* DescribeWidget;
	FTimerHandle DescribeHandle;

public:
	int32 GetWeaponSite() const;
	AWeapon* GetWeapon() const;
	FWeaponMsg GetWeaponMsg() const;

	void UpdateMsg(FWeaponMsg Out_WeaponMsg);
	void RemoveMsg();
	void UpdatePos();
	void RemoveDescribe();
	void Reload();

protected:
	virtual void NativePreConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	
};
