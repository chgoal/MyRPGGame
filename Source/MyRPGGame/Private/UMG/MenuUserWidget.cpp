// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MenuUserWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Controller/RPGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/ConfirmUserWidget.h"
#include "UMG/KeyUserWidget.h"

void UMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Quit->OnClicked.AddUniqueDynamic(this,&UMenuUserWidget::OnClick_Quit);
    Button_Set->OnClicked.AddUniqueDynamic(this,&UMenuUserWidget::OnClick_Set);
    Button_Screen->OnClicked.AddUniqueDynamic(this,&UMenuUserWidget::OnClick_Screen);
}

void UMenuUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	if (!KeyUserWidget)
	{
		TSubclassOf<UKeyUserWidget> KeyClass = LoadClass<UKeyUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_KeyWiget.UI_KeyWiget_C'"));
		KeyUserWidget = CreateWidget<UKeyUserWidget>(GetOwningPlayer(),KeyClass);
	}
	if (ARPGPlayerController* PlayerController = Cast<ARPGPlayerController>(GetOwningPlayer()))
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
}

void UMenuUserWidget::RemoveFromParent()
{
	if (ARPGPlayerController* PlayerController = Cast<ARPGPlayerController>(GetOwningPlayer()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(),false);
	}
	//GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	Super::RemoveFromParent();
	
}

void UMenuUserWidget::OnClick_Quit()
{
	if (!ConfirmUserWidget)
    {
    	TSubclassOf<UConfirmUserWidget> ConfirmClass = LoadClass<UConfirmUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_ConfirmWidget.UI_ConfirmWidget_C'"));
    	ConfirmUserWidget = CreateWidget<UConfirmUserWidget>(GetOwningPlayer(),ConfirmClass);
    }
	
	ConfirmUserWidget->AddToViewport();
}

void UMenuUserWidget::OnClick_Set()
{
	if (!KeyUserWidget)
	{
		TSubclassOf<UKeyUserWidget> KeyClass = LoadClass<UKeyUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_KeyWiget.UI_KeyWiget_C'"));
		KeyUserWidget = CreateWidget<UKeyUserWidget>(GetOwningPlayer(),KeyClass);
	}
	if (FellowUI)
	{
		FellowUI->ClearChildren();
		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(FellowUI->AddChildToOverlay(KeyUserWidget)))
		{
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
	}
}

void UMenuUserWidget::OnClick_Screen()
{
	if (!SettingWidget)
	{
		TSubclassOf<UKeyUserWidget> SetClass = LoadClass<UKeyUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_SettingWidget.UI_SettingWidget_C'"));
		SettingWidget = CreateWidget<UKeyUserWidget>(GetOwningPlayer(),SetClass);
	}
	if (FellowUI)
	{
		FellowUI->ClearChildren();
		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(FellowUI->AddChildToOverlay(SettingWidget)))
		{
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
	}
}
