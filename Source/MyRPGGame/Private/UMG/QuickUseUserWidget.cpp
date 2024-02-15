// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/QuickUseUserWidget.h"

#include "Characters/BaseCharacter.h"
#include "ActorComponent/PackageComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "UMG/DescribeUserWidget.h"
#include "UMG/ItemUserWidget.h"
#include "UMG/PackageUserWidget.h"
#include "UMG/PlayerHUD.h"

void UQuickUseUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (PropsSign)
	{
		FText SignText;
		switch (QuickUse)
		{
		case EQuickUse::EQU_QuickUse1:
			{
				SignText = NSLOCTEXT("QuickUse","k1","1");
				break;
			}
		case EQuickUse::EQU_QuickUse2:
			{
				SignText = NSLOCTEXT("QuickUse","k2","2");
				break;
			}
			default:
			{
				SignText = NSLOCTEXT("QuickUse","k10","None");
				break;
			}
		}
		PropsSign->SetText(SignText);
		UpdateIcon(SavedID);
	}
}

bool UQuickUseUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	
	if (UItemUserWidget* ItemWidget = Cast<UItemUserWidget>(InOperation->Payload))
	{
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
		{
			if (!ItemWidget->GetSceneItem())
			{
				LinkedSite = ItemWidget->GetItemSite();
				BaseCharacter->GetPackageComponent()->AddPropsToSocket(QuickUse,LinkedSite);
			}
		}
		
	}
	if (UQuickUseUserWidget* OtherUseWidget = Cast<UQuickUseUserWidget>(InOperation->Payload))
	{
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
		{
			BaseCharacter->GetPackageComponent()->PropsSocketExChange(OtherUseWidget->GetQuickUse(),QuickUse);
		}
	}
	return true;
}

FReply UQuickUseUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (PropsIcon->IsVisible())
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return FReply::Unhandled();
	}
}

void UQuickUseUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!DescribeUserWidget)
	{
		TSubclassOf<UDescribeUserWidget> DescribeClass = LoadClass<UDescribeUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Describe.UI_Describe_C'"));
		DescribeUserWidget = CreateWidget<UDescribeUserWidget>(GetOwningPlayer(),DescribeClass);
	}
	if (!PropsIcon->IsVisible())
	{
		return;
	}
	if (DescribeUserWidget)
	{
		if (DescribeUserWidget->IsInViewport())
		{
			return;
		}
		DescribeUserWidget->AddToViewport();
		DescribeUserWidget->SetDescribeID(EItemType::EPT_Tool,SavedID);
		UpdatePos();
	}
	if (APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetOwningPlayer()->GetHUD()))
	{
		PlayerHUD->GetPackageUserWidget()->OnScreenWidgetClose.AddUObject(this,&UQuickUseUserWidget::RemoveDescribe);
	}
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().SetTimer(DescribeHandle,this,&UQuickUseUserWidget::UpdatePos,0.01f,true);
}

void UQuickUseUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	//Super::NativeOnMouseLeave(InMouseEvent);
	if (DescribeUserWidget)
	{
		DescribeUserWidget->RemoveFromParent();
	}
	GetOwningPlayerPawn()->GetWorld()->GetTimerManager().ClearTimer(DescribeHandle);
}

void UQuickUseUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	//Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	OutOperation->Payload = this;
	OutOperation->DefaultDragVisual = this;
	OutOperation->Pivot = EDragPivot::MouseDown;
}

EPropsType UQuickUseUserWidget::GetPropsType() const
{
	const FPropsBase* PropsBase = GetOwningPlayer()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetPropsByID(SavedID);
	if (!PropsBase)
	{
		return EPropsType::EPT_None;
	}
	if (const FProps* Props = static_cast<const FProps*>(PropsBase))
	{
		return Props->PropsType;
	}
	return EPropsType::EPT_None;
}



void UQuickUseUserWidget::UpdateIcon(int32 ID)
{
	if (ID == -1)
	{
		PropsIcon->SetVisibility(ESlateVisibility::Hidden);
		PropsSign->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PropsIcon->SetVisibility(ESlateVisibility::Visible);
		PropsSign->SetVisibility(ESlateVisibility::Hidden);
		const FPropsBase* PropsBase = GetOwningPlayer()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetPropsByID(ID);
		if (PropsIcon)
		{
			PropsIcon->SetBrushFromTexture(PropsBase->Icon);
		}
	}
	SavedID = ID;
}

void UQuickUseUserWidget::UpdateMessage(int32 Out_ID,int32 Out_Site)
{
	UpdateIcon(Out_ID);
	LinkedSite = Out_Site;
}

bool UQuickUseUserWidget::InWitchBox(EQuickUse Out_QuickUse)
{
	switch (Out_QuickUse)
	{
	case EQuickUse::EQU_QuickUse1:
	case EQuickUse::EQU_QuickUse2:
	default:return false;
	}
}

int32 UQuickUseUserWidget::GetLinkedSite()
{
	return LinkedSite;
}

EQuickUse UQuickUseUserWidget::GetQuickUse()
{
	return QuickUse;
}

void UQuickUseUserWidget::SetLinkedSite(int32 Out_Site)
{
	LinkedSite = Out_Site;
}

void UQuickUseUserWidget::UpdatePos()
{
	if (DescribeUserWidget)
	{
		float X;
		float Y;
		GetOwningPlayer()->GetMousePosition(X,Y);
		DescribeUserWidget->SetPositionInViewport(FVector2D(X+2.f,Y+2.f));
	}
}

void UQuickUseUserWidget::RemoveDescribe()
{
	if (DescribeUserWidget)
	{
		if (DescribeUserWidget->IsInViewport())
		{
			DescribeUserWidget->RemoveFromParent();
		}
	}
}

void UQuickUseUserWidget::Reload()
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
	{
		TMap<EQuickUse,int32> UseMap;
		Character->GetPackageComponent()->GetPropsMap(UseMap);
		if (UseMap.Contains(QuickUse))
		{
			UpdateMessage(Character->GetPackageComponent()->GetPackageItemFromSite(UseMap[QuickUse]).ID,UseMap[QuickUse]);
		}
		else
		{
			UpdateMessage(-1,-1);
		}
	}
}
