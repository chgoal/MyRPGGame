// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/LoadSaveUserWidget.h"

#include "Characters/PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Controller/RPGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/MyRPGSaveGame.h"
#include "UMG/SaveGameBarUserWidget.h"

void ULoadSaveUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	UpdateSaveGameBar();
	if (ARPGPlayerController* Controller = Cast<ARPGPlayerController>(GetOwningPlayer()))
	{
		Controller->OnReloadSaveGame.AddUObject(this,&ULoadSaveUserWidget::UpdateSaveGameBar);
	}
}

void ULoadSaveUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//绑定
	Button_SaveGame->OnClicked.AddUniqueDynamic(this,&ULoadSaveUserWidget::SaveGameOnClick);
}



void ULoadSaveUserWidget::RemoveFromParent()
{
	Super::RemoveFromParent();
}

void ULoadSaveUserWidget::SaveGameOnClick()
{
	if (ARPGPlayerController* RPGPlayerController = Cast<ARPGPlayerController>(GetOwningPlayer()))
	{
		RPGPlayerController->SaveGame();
	}
	//如果有其他控制器在这添加
}
void ULoadSaveUserWidget::UpdateSaveGameBar()
{
	if (UWeaponSubsystem* WeaponSubsystem = GetOwningPlayer()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		if (SaveGameList)
		{
			SaveGameList->ClearChildren();
			TMap<FName,UMyRPGSaveGame*> SaveGames;
            WeaponSubsystem->GetSaveGames(SaveGames);
            for (auto Item:SaveGames)
            {
            	TSubclassOf<USaveGameBarUserWidget> SaveGameBarClass = LoadClass<USaveGameBarUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_SaveGameBar.UI_SaveGameBar_C'"));
            	USaveGameBarUserWidget* SaveGameBarUserWidget = CreateWidget<USaveGameBarUserWidget>(GetOwningPlayer(),SaveGameBarClass);
            	SaveGameList->AddChild(SaveGameBarUserWidget);
            	SaveGameBarUserWidget->UpdateSaveGameBar(Item.Value);
            }
		}
	}
}
