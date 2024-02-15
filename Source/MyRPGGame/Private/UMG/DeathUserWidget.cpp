// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/DeathUserWidget.h"


void UDeathUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	PlayWidgetAnimation();
}
