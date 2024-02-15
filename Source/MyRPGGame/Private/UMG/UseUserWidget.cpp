// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/UseUserWidget.h"

#include "AbilitySystemComponent.h"
#include "ActorComponent/PackageComponent.h"
#include "Characters/BaseCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Components/Button.h"
#include "Subsystem/WeaponSubsystem.h"

void UUseUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
}

void UUseUserWidget::OnClick_Yes()
{
	const FPropsBase* PropsBase = GetOwningPlayerPawn()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetPropsByID(ID);
	if (!PropsBase)
	{
		return;
	}
	if (const FProps* Props = static_cast<const FProps*>(PropsBase))
	{
		if (Props->AddPropsGameAbility.GetDefaultObject())
		{
			
			if (APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
			{
				Character->UseProps(Site);
			}

		}
	}
}

void UUseUserWidget::OnClick_No()
{
	RemoveFromParent();
}

void UUseUserWidget::InitWidget(int32 Out_ID,int32 Out_Site)
{
	ID = Out_ID;
	Site = Out_Site;
	Button_Yes->OnClicked.AddDynamic(this,&UUseUserWidget::OnClick_Yes);
	Button_No->OnClicked.AddDynamic(this,&UUseUserWidget::OnClick_No);
}
