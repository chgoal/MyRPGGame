// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/StartMenuUserWidget.h"

#include "Components/Overlay.h"
#include "UMG/StartListUserWidget.h"


UStartMenuUserWidget::UStartMenuUserWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	bIsFocusable = true;
}

FReply UStartMenuUserWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (NextWidget)
	{
		if (UStartListUserWidget* T_ListUserWidget = Cast<UStartListUserWidget>(NextWidget->GetChildAt(0)))
		{
			T_ListUserWidget->SelectChange(-InMouseEvent.GetWheelDelta());
			FWidgetTransform T_Transform = T_ListUserWidget->RenderTransform;
			T_Transform.Translation = FVector2D(T_Transform.Translation.X,MoveY*(T_ListUserWidget->GetSelectButton()-1));
			T_ListUserWidget->SetRenderTransform(T_Transform);
			
		}
	}
	return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
}

FReply UStartMenuUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UE_LOG(LogTemp, Log, TEXT("KeyDown"))
	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		UE_LOG(LogTemp, Log, TEXT("Enter"))
		if (NextWidget)
		{
			if (UStartListUserWidget* T_ListUserWidget = Cast<UStartListUserWidget>(NextWidget->GetChildAt(0)))
			{
				T_ListUserWidget->SelectKeyClick();
            }
		}
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}


