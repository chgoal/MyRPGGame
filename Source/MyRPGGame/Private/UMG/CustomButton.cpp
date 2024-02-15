// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/CustomButton.h"

#include "Components/ButtonSlot.h"
#include "SWidget/SSCustomButton.h"

static FButtonStyle* DefaultButtonStyle = nullptr;

TSharedRef<SWidget> UCustomButton::RebuildWidget()
{
	ButtonStyle = WidgetStyle;
	ButtonStyle.Normal = WidgetStyle.Hovered;
	
	if (bSelected)
	{
		MyButton = SNew(SButton)
				.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
				.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
				.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
				.OnHovered_UObject( this, &ThisClass::CustomSlateHandleHovered )
				.OnUnhovered_UObject( this, &ThisClass::CustomSlateHandleUnhovered )
				.ButtonStyle(&ButtonStyle)
				.ClickMethod(ClickMethod)
				.TouchMethod(TouchMethod)
				.PressMethod(PressMethod)
				.IsFocusable(IsFocusable)
				;
	}
	else
	{
		MyButton = SNew(SButton)
        		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
        		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
        		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
        		.OnHovered_UObject( this, &ThisClass::CustomSlateHandleHovered )
        		.OnUnhovered_UObject( this, &ThisClass::CustomSlateHandleUnhovered )
        		.ButtonStyle(&WidgetStyle)
        		.ClickMethod(ClickMethod)
        		.TouchMethod(TouchMethod)
        		.PressMethod(PressMethod)
        		.IsFocusable(IsFocusable)
        		;
	}
	

	if ( GetChildrenCount() > 0 )
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}
	
	return MyButton.ToSharedRef();
}

void UCustomButton::PostLoad()
{
	Super::PostLoad();
}

void UCustomButton::CustomSlateHandleHovered()
{
	
	if (OnCustomButtonHover.IsBound())
	{
		OnCustomButtonHover.Broadcast(Serial);
	}
	OnHovered.Broadcast();
}

void UCustomButton::CustomSlateHandleUnhovered()
{
	
	if (OnCustomButtonUnHover.IsBound())
	{
		OnCustomButtonUnHover.Broadcast(Serial);
	}
	OnUnhovered.Broadcast();
}


UCustomButton::UCustomButton(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	if (DefaultButtonStyle == nullptr)
	{
		// HACK: THIS SHOULD NOT COME FROM CORESTYLE AND SHOULD INSTEAD BE DEFINED BY ENGINE TEXTURES/PROJECT SETTINGS
		DefaultButtonStyle = new FButtonStyle(FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"));

		// Unlink UMG default colors from the editor settings colors.
		DefaultButtonStyle->UnlinkColors();
	}
	ButtonStyle = *DefaultButtonStyle;
	Serial = -1;
}

void UCustomButton::SetSerial(int32 Out_Serial)
{
	Serial = Out_Serial;
}
void UCustomButton::SetSelect(bool Out_Selected)
{
	bSelected = Out_Selected;
	if (MyButton)
	{
		if (bSelected)
		{
			MyButton->SetButtonStyle(&ButtonStyle);
		}
		else
		{
			MyButton->SetButtonStyle(&WidgetStyle);
		}
	}
	
}

int32 UCustomButton::GetSerial()
{
	return Serial;
}




