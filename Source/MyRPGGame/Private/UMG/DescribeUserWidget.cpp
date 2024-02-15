// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/DescribeUserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystem/WeaponSubsystem.h"

void UDescribeUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	MItem = EItemType::EPT_Skin;
	MID = -1;
}

void UDescribeUserWidget::SetDescribeID(EItemType Item, int32 ID)
{
	if (ID == -1)
	{
		MItem = Item;
		MID = ID;
		NameText->SetText(FText::FromString(TEXT(" ")));
		Icon->SetBrushFromTexture(nullptr);
		Icon->SetVisibility(ESlateVisibility::Hidden);
		DescribeText->SetText(FText::FromString(TEXT(" ")));
		return;
	}
	if (NameText && DescribeText && Icon)
	{
		MItem = Item;
		MID = ID;
		if (const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetItemByIDAndType(ID,Item))
		{
			NameText->SetText(PropsBase->Name);
			Icon->SetBrushFromTexture(PropsBase->Icon);
			Icon->SetVisibility(ESlateVisibility::Visible);
			DescribeText->SetText(FText::FromString(PropsBase->description));
		}
	}
}

void UDescribeUserWidget::ClearDescribeID()
{
	if (NameText && DescribeText && Icon)
	{
		NameText->SetText(FText::FromString(TEXT(" ")));
		Icon->SetBrushFromTexture(nullptr);
		DescribeText->SetText(FText::FromString(TEXT(" ")));
		MItem = EItemType::EPT_Skin;
		MID = -1;
	}
}
