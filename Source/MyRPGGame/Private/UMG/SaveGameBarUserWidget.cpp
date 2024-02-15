// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/SaveGameBarUserWidget.h"

#include "Characters/PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/RPGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/MyRPGSaveGame.h"

void USaveGameBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SaveButton->OnClicked.AddDynamic(this,&USaveGameBarUserWidget::OnDoubleClick);
}

void USaveGameBarUserWidget::UpdateSaveGameBar(UMyRPGSaveGame* RPGSaveGame)
{
	MyRPGSaveGame = RPGSaveGame;
	if (MyRPGSaveGame)
	{
		if (SaveTime && SaveMsg)
		{
			SaveTime->SetText(FText::FromString(MyRPGSaveGame->SaveTime));
			TArray<FStringFormatArg> args;
			args.Add(FMath::RoundToInt(MyRPGSaveGame->Health));
			args.Add(FMath::RoundToInt(MyRPGSaveGame->Mana));
			args.Add(FMath::RoundToInt(MyRPGSaveGame->Stamina));
			SaveMsg->SetText(FText::FromString(FString::Format(TEXT("生命:{0},能量:{1},体力:{2}"),args)));
		}
	}
}

void USaveGameBarUserWidget::OnDoubleClick()
{
	if (MyRPGSaveGame)
	{
		if (UWeaponSubsystem* WeaponSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
        {
        	WeaponSubsystem->SetSelectSaveGame(MyRPGSaveGame);
			UGameplayStatics::OpenLevel(GetWorld(),MyRPGSaveGame->LevelName);
        }
	}
}

void USaveGameBarUserWidget::LoadGame()
{
	if (MyRPGSaveGame)
	{
		if (ARPGPlayerController* Controller = Cast<ARPGPlayerController>(GetOwningPlayer()))
        {
        	Controller->LoadGame();
        }
	}
}
