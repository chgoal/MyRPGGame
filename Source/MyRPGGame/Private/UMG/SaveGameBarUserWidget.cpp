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
			FText Time;
			TransformLoadTime(MyRPGSaveGame->SaveTime,Time);
			SaveTime->SetText(Time);
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

bool USaveGameBarUserWidget::TransformLoadTime(FString TimeString,FText& TimeText)
{
	FString LeftS;
	FString RightS;
	if (TimeString.Split(TEXT("-"),&LeftS,&RightS))
	{
		TArray<FString> LeftSArray;
		TArray<FString> RightSArray;
		TArray<FStringFormatArg> LArgs;
		TArray<FStringFormatArg> RArgs;
		LeftS.ParseIntoArray(LeftSArray,TEXT("."),false);
		RightS.ParseIntoArray(RightSArray,TEXT("."),false);
		for (auto It: LeftSArray)
		{
			LArgs.Add(FStringFormatArg(It));
		}
		for (auto It: RightSArray)
		{
			RArgs.Add(FStringFormatArg(It));
		}
		FString Date = FString::Format(TEXT("{0}年{1}月{2}日   "),LArgs);
		FString Time = FString::Format(TEXT("{0}点{1}分{2}秒"),RArgs);
		TimeText = FText::FromString(Date.Append(Time));
		return true;
	}
	return false;
}
