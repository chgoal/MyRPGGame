// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PlayerUserWidget.h"

#include "ActorComponent/PackageComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Components/HorizontalBox.h"
#include "UMG/BoundKeyUserWidget.h"

void UPlayerUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (Player->GetPackageComponent())
		{
			Player->GetPackageComponent()->OnPropsBoundAdded.AddUObject(this,&UPlayerUserWidget::BoundProps);
			Player->GetPackageComponent()->OnPropsBoundRemove.AddUObject(this,&UPlayerUserWidget::UnBoundProps);
			Player->GetPackageComponent()->OnPropsRemoveAll.AddUObject(this,&UPlayerUserWidget::UnBoundAllProps);
		}
	}
}

void UPlayerUserWidget::RemoveFromParent()
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (Player->GetPackageComponent())
		{
			Player->GetPackageComponent()->OnPropsBoundAdded.RemoveAll(this);
			Player->GetPackageComponent()->OnPropsBoundRemove.RemoveAll(this);
		}
	}
	Super::RemoveFromParent();
}


void UPlayerUserWidget::BoundProps(EQuickUse Out_QuickUse, int32 Out_Site, int32 Out_ID) const
{
	if (BoundHorizon)
	{
		for (auto Widget : BoundHorizon->GetAllChildren())
		{
			if (UBoundKeyUserWidget* BoundWidget = Cast<UBoundKeyUserWidget>(Widget))
			{
				if (BoundWidget->GetQuickUse() == Out_QuickUse)
				{
					BoundWidget->UpdateWidget(Out_ID);
				}
			}
		}
	}
}

void UPlayerUserWidget::UnBoundProps(EQuickUse Out_QuickUse, int32 Out_Site, int32 Out_ID) const
{
	if (BoundHorizon)
	{
		for (auto Widget : BoundHorizon->GetAllChildren())
		{
			if (UBoundKeyUserWidget* BoundWidget = Cast<UBoundKeyUserWidget>(Widget))
			{
				if (BoundWidget->GetQuickUse() == Out_QuickUse)
				{
					BoundWidget->UpdateWidget(-1);
				}
			}
		}
	}
}

void UPlayerUserWidget::UnBoundAllProps() const
{
	if (BoundHorizon)
	{
		for (auto Widget : BoundHorizon->GetAllChildren())
		{
			if (UBoundKeyUserWidget* BoundWidget = Cast<UBoundKeyUserWidget>(Widget))
			{
				BoundWidget->UpdateWidget(-1);
			}
		}
	}
}

