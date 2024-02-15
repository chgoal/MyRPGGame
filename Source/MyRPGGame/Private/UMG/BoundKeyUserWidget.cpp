// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/BoundKeyUserWidget.h"

#include "Components/Image.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/WeaponSubsystem.h"


void UBoundKeyUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (BoundIcon)
	{
		BoundIcon->SetVisibility(ESlateVisibility::Hidden);
		BoundIcon->SetBrushFromTexture(nullptr);
	}
	
}

void UBoundKeyUserWidget::UpdateWidget(int32 Out_ID)
{
	SavedID = Out_ID;
	if (Out_ID == -1)
	{
		if (BoundIcon)
		{
			BoundIcon->SetVisibility(ESlateVisibility::Hidden);
			BoundIcon->SetBrushFromTexture(nullptr);
		}
		
		return;
	}
	const FPropsBase* PropsBase = GetOwningPlayerPawn()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetPropsByID(Out_ID);
	if (!PropsBase)
	{
		return;
	}
	const FProps* Props = static_cast<const FProps*>(PropsBase);
	if (!Props)
	{
		return;
	}
	{
		if (BoundIcon)
		{
			BoundIcon->SetVisibility(ESlateVisibility::Visible);
			BoundIcon->SetBrushFromTexture(Props->Icon);
		}
	}
}

EQuickUse UBoundKeyUserWidget::GetQuickUse()
{
	return QuickUse;
}

FName UBoundKeyUserWidget::ConvertQuickUseToName(EQuickUse T_QuickUse)
{
	switch (T_QuickUse)
	{
	case EQuickUse::EQU_QuickUse1:return TEXT("PropertyPanel1");break;
	case EQuickUse::EQU_QuickUse2:return TEXT("PropertyPanel2");break;
		default:return TEXT("");break;
	}
}

FText UBoundKeyUserWidget::GetBoundKeyText()
{
	TArray<FInputActionKeyMapping> KeyMappings;
	UInputSettings::GetInputSettings()->GetActionMappingByName(ConvertQuickUseToName(QuickUse),KeyMappings);
	return FText::FromName(KeyMappings[0].Key.GetFName());
}
