// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/SkinSocketUserWidget.h"

#include "ActorComponent/PackageComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "UMG/DescribeUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UMG/ItemUserWidget.h"



void USkinSocketUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (SkinSign)
	{
		FText SignText;
		switch (SkinType)
		{
		case ESkinType::EST_Bag:
			{
				SignText = NSLOCTEXT("FramWidget","k1","包");
				break;
			}
		case ESkinType::EST_Armour:
			{
				SignText = NSLOCTEXT("FramWidget","k2","甲");
				break;
			}
		case ESkinType::EST_Helment:
			{
				SignText = NSLOCTEXT("FramWidget","k3","头");
				break;
			}
		case ESkinType::EST_Leggings:
			{
				SignText = NSLOCTEXT("FramWidget","k4","脚");
				break;
			}
		default:
			{
				SignText = NSLOCTEXT("FramWidget","k20","其他");
                break;
			}
				
		}
		SkinSign->SetText(SignText);
		UpdateIcon(SavedID);
	}
}

bool USkinSocketUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(InOperation->Payload))
	{
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
    	{
			if (ItemUserWidget->GetSceneItem())
        	{
				BaseCharacter->GetPackageComponent()->PutinSkin(ItemUserWidget->GetSceneItem());
            }
			else
			{
				BaseCharacter->GetPackageComponent()->PutinSkinFromPackage(ItemUserWidget->GetItemSite());
			}
		}
		
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply USkinSocketUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (SkinIcon->IsVisible())
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return FReply::Unhandled();
	}
}

void USkinSocketUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!DescribeWidget)
	{
		TSubclassOf<UDescribeUserWidget> DescribeClass = LoadClass<UDescribeUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Describe.UI_Describe_C'"));
		DescribeWidget = CreateWidget<UDescribeUserWidget>(GetOwningPlayer(),DescribeClass);
	}
	if (!SkinIcon->IsVisible())
	{
		return;
	}
	if (DescribeWidget)
	{
		DescribeWidget->SetDescribeID(EItemType::EPT_Skin,SavedID);
		if (DescribeWidget->IsInViewport())
		{
			return;
		}
		DescribeWidget->AddToViewport();
		UpdatePos();
	}
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().SetTimer(DescribeHandle,this,&USkinSocketUserWidget::UpdatePos,0.01f,true);
	//Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void USkinSocketUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	//Super::NativeOnMouseLeave(InMouseEvent);
	if (DescribeWidget)
	{
		DescribeWidget->RemoveFromParent();
	}
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().ClearTimer(DescribeHandle);
}

void USkinSocketUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                 UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->Payload = this;
	OutOperation->DefaultDragVisual = this;
	OutOperation->Pivot = EDragPivot::MouseDown;
}

ESkinType USkinSocketUserWidget::GetSkinType() const
{
	return SkinType;
}

void USkinSocketUserWidget::UpdateIcon(int32 ID)
{
	if (ID == -1)
	{
		SkinIcon->SetVisibility(ESlateVisibility::Hidden);
		SkinSign->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SkinIcon->SetVisibility(ESlateVisibility::Visible);
		SkinSign->SetVisibility(ESlateVisibility::Hidden);
		const FPropsBase* PropsBase = GetOwningPlayer()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetSkinByID(ID);
		if (SkinIcon)
		{
			SkinIcon->SetBrushFromTexture(PropsBase->Icon);
		}
	}
	SavedID = ID;
}

void USkinSocketUserWidget::Reload()
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
	{
		TMap<ESkinType,int32> SkinItem;
		Character->GetPackageComponent()->GetSkinMap(SkinItem);
		if (SkinItem.Contains(SkinType))
		{
			UpdateIcon(SkinItem[SkinType]);
		}
		else
		{
			UpdateIcon(-1);
		}
	}
}

bool USkinSocketUserWidget::InWitchBox(ESkinType Out_SkinType)
{
	switch (Out_SkinType)
	{
	case ESkinType::EST_Helment:
	case ESkinType::EST_Armour:
	case ESkinType::EST_Bag:
	case ESkinType::EST_Leggings:
	case ESkinType::EST_NONE:
		default: return false;
	}
}

void USkinSocketUserWidget::UpdatePos()
{
	if (DescribeWidget)
	{
		float X;
		float Y;
		GetOwningPlayer()->GetMousePosition(X,Y);
		DescribeWidget->SetPositionInViewport(FVector2D(X+2.f,Y+2.f));
	}
}

void USkinSocketUserWidget::RemoveDescribe()
{
	if (DescribeWidget)
	{
		if (DescribeWidget->IsInViewport())
		{
			DescribeWidget->RemoveFromParent();
		}
	}
}
