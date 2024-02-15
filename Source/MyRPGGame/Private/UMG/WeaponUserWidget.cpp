// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WeaponUserWidget.h"

#include "ActorComponent/PackageComponent.h"
#include "Actors/SceneItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Components/Image.h"
#include "UMG/DescribeUserWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "UMG/ItemUserWidget.h"

void UWeaponUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (WeaponSite)
	{
		WeaponSite->SetText(FText::AsNumber(Site));
	}
	if (WeaponMax)
	{
		WeaponMax->SetText(FText::AsNumber(TotalBullet));
	}
	if (WeaponGroup)
	{
		WeaponGroup->SetText(FText::AsNumber(CurrentBullet));
	}
}

bool UWeaponUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(InOperation->Payload))
	{
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
		{
			if (ItemUserWidget->GetSceneItem())
			{
				BaseCharacter->GetPackageComponent()->AddWeaponToPackage(Site,ItemUserWidget->GetSceneItem());
			}
			//武器可以输出的直接为ScenceItem;
		}
	}
	if (UWeaponUserWidget* WeaponUserWidget = Cast<UWeaponUserWidget>(InOperation->Payload))
	{
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
		{
			BaseCharacter->GetPackageComponent()->ExchangeWeapon(Site,WeaponUserWidget->GetWeaponSite());
		}
	}
	return true;
}

FReply UWeaponUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (WeaponIcon->IsVisible())
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return FReply::Unhandled();
	}
	
}

void UWeaponUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!DescribeWidget)
	{
		TSubclassOf<UDescribeUserWidget> DescribeClass = LoadClass<UDescribeUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Describe.UI_Describe_C'"));
		DescribeWidget = CreateWidget<UDescribeUserWidget>(GetOwningPlayer(),DescribeClass);
	}
	if (!WeaponIcon->IsVisible())
	{
		return;
	}
	if (DescribeWidget)
	{
		if (DescribeWidget->IsInViewport())
		{
			return;
		}
	
		DescribeWidget->SetDescribeID(EItemType::EPT_Weapon,WeaponMsg.ID);

		DescribeWidget->AddToViewport();
		UpdatePos();
	}

	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().SetTimer(DescribeHandle,this,&UWeaponUserWidget::UpdatePos,0.01f,true);
	//Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UWeaponUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (DescribeWidget)
	{
		DescribeWidget->RemoveFromParent();
	}
	//Super::NativeOnMouseLeave(InMouseEvent);
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().ClearTimer(DescribeHandle);
}



void UWeaponUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                             UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->DefaultDragVisual = this;
	OutOperation->Payload = this;
	OutOperation->Pivot = EDragPivot::MouseDown;
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}



int32 UWeaponUserWidget::GetWeaponSite() const
{
	return Site;
}

AWeapon* UWeaponUserWidget::GetWeapon() const
{
	return Weapon;
}

FWeaponMsg UWeaponUserWidget::GetWeaponMsg() const
{
	return WeaponMsg;
}

void UWeaponUserWidget::UpdateMsg(FWeaponMsg Out_WeaponMsg)
{
	WeaponMsg = Out_WeaponMsg;
	if (Out_WeaponMsg.ID == -1)
	{
		
		RemoveMsg();
	}
	else
	{
		WeaponIcon->SetVisibility(ESlateVisibility::Visible);
		const FPropsBase* PropsBase = GetOwningPlayer()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetWeaponsByID(WeaponMsg.ID);
        if (!PropsBase || PropsBase->ItemType!=EItemType::EPT_Weapon)
        {
        	return;
        }
        if (const FWeapons* Weapons = static_cast<const FWeapons*>(PropsBase) )
        {
        	if (WeaponIcon)
        	{
        		WeaponIcon->SetBrushFromTexture(Weapons->WeaponIcon);
        	}
        	if (WeaponMax)
        	{
        		WeaponMax->SetText(FText::AsNumber(WeaponMsg.MaxBullet));
        	}
        	if (WeaponGroup)
        	{
        		WeaponGroup->SetText(FText::AsNumber(WeaponMsg.CurrentBullet));
        	}
        }
	}
	
}

void UWeaponUserWidget::RemoveMsg()
{
	const FWeaponMsg TWeaponMsg;
	WeaponMsg = TWeaponMsg;
	if (WeaponIcon)
	{
		WeaponIcon->SetVisibility(ESlateVisibility::Hidden);
		WeaponIcon->SetBrushFromTexture(nullptr);
	}
	if (WeaponMax)
	{
		WeaponMax->SetText(FText::FromString(TEXT(" ")));
	}
	if (WeaponGroup)
	{
		WeaponGroup->SetText(FText::FromString(TEXT(" ")));
	}
}

void UWeaponUserWidget::UpdatePos()
{
	if (DescribeWidget)
	{
		float X;
		float Y;
		GetOwningPlayer()->GetMousePosition(X,Y);
		DescribeWidget->SetPositionInViewport(FVector2D(X+2.f,Y+2.f));
	}
}

void UWeaponUserWidget::RemoveDescribe()
{
	if (DescribeWidget)
	{
		if (DescribeWidget->IsInViewport())
		{
			DescribeWidget->RemoveFromParent();
		}
	}
}

void UWeaponUserWidget::Reload()
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
	{
		TMap<int32,FWeaponMsg> WeaponMap;
		Character->GetPackageComponent()->GetWeaponMap(WeaponMap);
		if (WeaponMap.Contains(Site))
		{
			UpdateMsg(WeaponMap[Site]);
		}
		else
		{
			FWeaponMsg T_WeaponMsg;
			T_WeaponMsg.ID = -1;
			UpdateMsg(T_WeaponMsg);
		}
	}
}


