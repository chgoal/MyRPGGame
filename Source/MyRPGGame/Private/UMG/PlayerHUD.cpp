// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PlayerHUD.h"
#include "UMG/PackageUserWidget.h"
#include "UMG/MenuUserWidget.h"
#include "UMG/PlayerUserWidget.h"
#include "UMG/DeathUserWidget.h"
#include "UMG/StartMenuUserWidget.h"
#include "UMG/LoadSaveUserWidget.h"
#include "UMG/LoginUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

bool APlayerHUD::TogglePackage()
{
	if (!PackageUI)
	{
		TSubclassOf<UPackageUserWidget> PackageClass = LoadClass<UPackageUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Package.UI_Package_C'"));
		PackageUI = CreateWidget<UPackageUserWidget>(GetOwningPlayerController(),PackageClass);
	}
	if (PackageUI)
	{
		if (PackageUI->IsInViewport())
		{
			PackageUI->RemoveFromParent();
			GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
		}
		else
		{
			PackageUI->AddToViewport();
			GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
		}
		
		GetOwningPlayerController()->bShowMouseCursor = PackageUI->IsInViewport();
	}
	return PackageUI->IsInViewport();
}

bool APlayerHUD::ToggleMainMenu()
{
	if (!MenuUserWidget)
	{
		TSubclassOf<UMenuUserWidget> MenuClass = LoadClass<UMenuUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Menu.UI_Menu_C'"));
		MenuUserWidget = CreateWidget<UMenuUserWidget>(GetOwningPlayerController(),MenuClass);
	}
	if (MenuUserWidget)
	{
		if (MenuUserWidget->IsInViewport())
		{
			MenuUserWidget->RemoveFromParent();
		}
		else
		{
			MenuUserWidget->AddToViewport();
		}
		GetOwningPlayerController()->bShowMouseCursor = MenuUserWidget->IsInViewport();
	}
	return MenuUserWidget->IsInViewport();
}

bool APlayerHUD::TogglePlayerMenu()
{
	if (!PlayerUserWidget)
	{
		TSubclassOf<UPlayerUserWidget> PlayerClass = LoadClass<UPlayerUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_PlayerWidget.UI_PlayerWidget_C'"));
		PlayerUserWidget = CreateWidget<UPlayerUserWidget>(GetOwningPlayerController(),PlayerClass);
	}
	if (PlayerUserWidget)
	{
		if (PlayerUserWidget->IsInViewport())
		{
			PlayerUserWidget->RemoveFromParent();
		}
		else
		{
			PlayerUserWidget->AddToViewport();
		}
	}
	return PlayerUserWidget->IsInViewport();
}

bool APlayerHUD::OpenDeathWidget(bool bOpen)
{
	if (!DeathUserWidget)
	{
		TSubclassOf<UDeathUserWidget> DeathClass = LoadClass<UDeathUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_DeathWidget.UI_DeathWidget_C'"));
		DeathUserWidget = CreateWidget<UDeathUserWidget>(GetOwningPlayerController(),DeathClass);
	}
	if (DeathUserWidget)
	{
		if (bOpen)
		{
			if (!DeathUserWidget->IsInViewport())
			{
				DeathUserWidget->AddToViewport();
				return true;
			}
		}
		else
		{
			if (DeathUserWidget->IsInViewport())
			{
				DeathUserWidget->RemoveFromParent();
				return true;
			}
		}
	}
	return false;
}

bool APlayerHUD::OpenStartMenuWidget(bool bOpen)
{
	if (!StartMenuUserWidget)
	{
		TSubclassOf<UStartMenuUserWidget> StartMenuClass = LoadClass<UStartMenuUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_StartMenu.UI_StartMenu_C'"));
		StartMenuUserWidget = CreateWidget<UStartMenuUserWidget>(GetOwningPlayerController(),StartMenuClass);
	}
	if (StartMenuUserWidget)
	{
		if (bOpen)
		{
			if (!StartMenuUserWidget->IsInViewport())
			{
				StartMenuUserWidget->AddToViewport();
				return true;
			}
		}
		else
		{
			if (StartMenuUserWidget->IsInViewport())
			{
				StartMenuUserWidget->RemoveFromParent();
				return true;
			}
		}
	}
	return false;
}

void APlayerHUD::OpenLoadSaveGame(bool bOpen)
{
	if (!LoadSaveUserWidget)
	{
		TSubclassOf<ULoadSaveUserWidget> LoadSaveClass = LoadClass<ULoadSaveUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_LoadSave.UI_LoadSave_C'"));
		LoadSaveUserWidget = CreateWidget<ULoadSaveUserWidget>(GetOwningPlayerController(),LoadSaveClass);
	}
	if (LoadSaveUserWidget)
	{
		if (bOpen)
		{
			if (!LoadSaveUserWidget->IsInViewport())
			{
				LoadSaveUserWidget->AddToViewport();
				
			}
		}
		else
		{
			if (LoadSaveUserWidget->IsInViewport())
			{
				LoadSaveUserWidget->RemoveFromParent();
			}
		}
	}
	
}


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	TogglePlayerMenu();
	//OpenStartMenuWidget(true);
}

UPackageUserWidget* APlayerHUD::GetPackageUserWidget() const
{
	return PackageUI;
}

UMenuUserWidget* APlayerHUD::GetMenuUserWidget() const
{
	return MenuUserWidget;
}

UPlayerUserWidget* APlayerHUD::GetPlayerUserWidget() const
{
	return PlayerUserWidget;
}

UDeathUserWidget* APlayerHUD::GetDeathUserWidget() const
{
	return DeathUserWidget;
}



