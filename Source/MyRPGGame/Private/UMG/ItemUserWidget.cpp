// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemUserWidget.h"
#include "UMG/UseUserWidget.h"

#include "Actors/SceneItem.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "UMG/DescribeUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

FReply UItemUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton).NativeReply;
}

void UItemUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->DefaultDragVisual = this;
	OutOperation->Payload = this;
	OutOperation->Pivot = EDragPivot::MouseDown;
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UItemUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!DescribeWidget)
	{
		TSubclassOf<UDescribeUserWidget> DescribeClass = LoadClass<UDescribeUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Describe.UI_Describe_C'"));
		DescribeWidget = CreateWidget<UDescribeUserWidget>(GetOwningPlayer(),DescribeClass);
	}
	if (BackGround)
	{
		BackGround->SetPadding(FMargin(2.f,3.f,2.f,1.f));
		BackGround->SetBrushColor(FLinearColor(1,1,1,0.2));
	}
	if (DescribeWidget)
	{
		DescribeWidget->SetDescribeID(Item,ID);
		if (DescribeWidget->IsInViewport())
		{
			return;
		}
		DescribeWidget->AddToViewport();
		UpdatePos();
	}
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().SetTimer(DescribeHandle,this,&UItemUserWidget::UpdatePos,0.01f,true);
	//Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UItemUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	//Super::NativeOnMouseLeave(InMouseEvent);
	if (DescribeWidget)
	{
		DescribeWidget->ClearDescribeID();
		DescribeWidget->RemoveFromParent();
	}
	if (BackGround)
	{
		BackGround->SetPadding(FMargin(0.f,0.f,0.f,0.f));
		BackGround->SetBrushColor(FLinearColor(1,1,1,0.2));
	}
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().ClearTimer(DescribeHandle);
}

FReply UItemUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!UseWidget)
	{
		TSubclassOf<UUseUserWidget> UseClass = LoadClass<UUseUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_UseWidget.UI_UseWidget_C'"));
		UseWidget = CreateWidget<UUseUserWidget>(GetOwningPlayer(),UseClass);
	}
	if (!bInPackage)
	{
		return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	}
	if (Item != EItemType::EPT_Tool)
	{
		return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	}
	if (!ItemVertical->HasChild(UseWidget))
	{
		ItemVertical->AddChildToVerticalBox(UseWidget);
		//UseWidget->ItemUse.AddUObject(this,&UItemUserWidget::UseProps);
		UseWidget->InitWidget(ID,ItemSite);
	}
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UItemUserWidget::RemoveFromParent()
{
	if (DescribeWidget)
	{
		DescribeWidget->RemoveFromParent();
	}
	
	Super::RemoveFromParent();
}

void UItemUserWidget::ResetPanel()
{
	if (DescribeWidget)
	{
		DescribeWidget->RemoveFromParent();
	}
	if (ItemVertical->HasChild(UseWidget))
	{
		UseWidget->RemoveFromParent();
		ItemVertical->RemoveChild(UseWidget);
	}
}

void UItemUserWidget::InitPanel(int32 Site, FIDAndType IDAndType)
{
	const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetItemByIDAndType(IDAndType);
	if (PropsBase)
	{
		Name->SetText(PropsBase->Name);
		Icon->SetBrushFromTexture(PropsBase->Icon);
		Item = IDAndType.ItemType;
		ID = IDAndType.ID;
		bInPackage = true;
		if (Item == EItemType::EPT_Tool)
		{
			Number = IDAndType.Number;
			Num->SetText(FText::AsNumber(Number));
		}
		else
		{
			Num->SetText(FText::FromString(TEXT(" ")));
		}
	}
	ItemSite = Site;
}

void UItemUserWidget::InitPanel(ASceneItem* SceneItem)
{
	if (!SceneItem)
	{
		return;
	}
	
	const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetItemByIDAndType(SceneItem->GetID(),SceneItem->GetItemType());
    if (PropsBase)
    {
	    ISceneItem = SceneItem;
    	Name->SetText(PropsBase->Name);
    	Icon->SetBrushFromTexture(PropsBase->Icon);
    	Item = SceneItem->GetItemType();
    	ID = SceneItem->GetID();
    	if (Item == EItemType::EPT_Tool)
    	{
    		Number = SceneItem->GetNumber();
    		Num->SetText(FText::AsNumber(Number));
    	}
        else
        {
	        Num->SetText(FText::FromString(TEXT(" ")));
        }
    }
	 
}

bool UItemUserWidget::GetInPackage()
{
	return bInPackage;
}

EItemType UItemUserWidget::GetItemType()
{
	return Item;
}

int32 UItemUserWidget::GetNumber()
{
	return Number;
}

ASceneItem* UItemUserWidget::GetSceneItem()
{
	return ISceneItem;
}

int32 UItemUserWidget::GetItemSite()
{
	return ItemSite;
}

void UItemUserWidget::AddNumber(int32 Add_Number)//道具类才可以添加数量
{
	if (Item == EItemType::EPT_Tool)
	{
		Number = Number+Add_Number;
		Num->SetText(FText::AsNumber(Number));
	}
}

void UItemUserWidget::SetInPackage(bool Out_InPackage)
{
	bInPackage = Out_InPackage;
}

void UItemUserWidget::UpdatePos()
{
	if (DescribeWidget)
	{
		float X;
		float Y;
		GetOwningPlayer()->GetMousePosition(X,Y);
		DescribeWidget->SetPositionInViewport(FVector2D(X+2.f,Y+2.f));
	}
}

void UItemUserWidget::RemoveDescribe()
{
	if (DescribeWidget)
	{
		if (DescribeWidget->IsInViewport())
		{
			DescribeWidget->RemoveFromParent();
		}
	}
}


