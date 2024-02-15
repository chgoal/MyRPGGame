// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/StartListUserWidget.h"

#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/MyRPGSaveGame.h"
#include "Subsystem/WeaponSubsystem.h"
#include "UMG/CustomButton.h"


void UStartListUserWidget::OnHovered(int32 Serial)
{
	//UE_LOG(LogTemp, Log, TEXT("OnHovered  Serial = %d"),Serial)
	if (SelectButton == Serial)
	{
		return;
	}
	else
	{
		if (ButtonVertical)
		{
			if (UCustomButton* CustomButton = Cast<UCustomButton>(ButtonVertical->GetChildAt(SelectButton)))
			{
				CustomButton->SetSelect(false);
			}
			if (UCustomButton* CustomButton = Cast<UCustomButton>(ButtonVertical->GetChildAt(Serial)))
			{
				CustomButton->SetSelect(true);
			}
			SelectButton = Serial;
		}
	}
}

void UStartListUserWidget::OnUnHovered(int32 Serial)
{
	//UE_LOG(LogTemp, Log, TEXT("UnHovered  Serial = %d"),Serial)
	if (SelectButton == Serial)
	{
		return;
	}
	else
	{
		if (UCustomButton* CustomButton = Cast<UCustomButton>(ButtonVertical->GetChildAt(Serial)))
		{
			CustomButton->SetSelect(false);
		}
	}
}

void UStartListUserWidget::SelectKeyClick()
{
	if (ButtonVertical)
	{
		if(UCustomButton* CustomButton = Cast<UCustomButton>(ButtonVertical->GetChildAt(SelectButton)))
		{
			CustomButton->OnClicked.Broadcast();		
		}
	}
}

void UStartListUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (ButtonVertical)
	{
		MaxButton = ButtonVertical->GetAllChildren().Num();
		int32 i = 0;
		for (auto Widget : ButtonVertical->GetAllChildren())
		{
			if (UCustomButton* CustomButton = Cast<UCustomButton>(Widget))
			{
				if (CustomButton->GetSerial() == -1)
				{
					CustomButton->SetSerial(i);
					CustomButton->OnCustomButtonHover.AddUObject(this,&UStartListUserWidget::OnHovered);
					CustomButton->OnCustomButtonUnHover.AddUObject(this,&UStartListUserWidget::OnUnHovered);
					i=i+1;
				}
			}
		}
		if (UCustomButton* CustomButton = Cast<UCustomButton>(ButtonVertical->GetChildAt(0)))
		{
			CustomButton->SetSelect(true);
		}
	}
	
}

void UStartListUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ButtonVertical)
	{
		MaxButton = ButtonVertical->GetAllChildren().Num();
	}
	if (ContinueGame)
	{
		ContinueGame->OnClicked.AddDynamic(this,&UStartListUserWidget::OnClick_ContinueGame);
	}
}

void UStartListUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	if (ButtonVertical)
	{
		MaxButton = ButtonVertical->GetAllChildren().Num();
	}
}

void UStartListUserWidget::SelectChange(int32 Delta)
{
	if (SelectButton+Delta>=0 && SelectButton+Delta<=MaxButton-1)
	{
		if (ButtonVertical)
		{
			if (UCustomButton* Button = Cast<UCustomButton>(ButtonVertical->GetChildAt(SelectButton)))
			{
				Button->SetSelect(false);
			}
			SelectButton+=Delta;
			if (UCustomButton* Button = Cast<UCustomButton>(ButtonVertical->GetChildAt(SelectButton)))
			{
				Button->SetSelect(true);
			}
		}
		
	}
}

int32 UStartListUserWidget::GetSelectButton()
{
	return SelectButton;
}

void UStartListUserWidget::OnClick_ContinueGame()
{
	if (UWeaponSubsystem* WeaponSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		TMap<FName,UMyRPGSaveGame*> SaveGames;
		WeaponSubsystem->GetSaveGames(SaveGames);
		if (SaveGames.begin())
		{
			WeaponSubsystem->SetSelectSaveGame(SaveGames.begin().Value());
			UGameplayStatics::OpenLevel(GetWorld(),SaveGames.begin().Value()->LevelName);
		}
	}
	
}
