// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class ULoadSaveUserWidget;
class ULoginUserWidget;
class UStartMenuUserWidget;
class UDeathUserWidget;
class UPlayerUserWidget;
class UConfirmUserWidget;
class UMenuUserWidget;
class UPackageUserWidget;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	bool TogglePackage();
	//void PlayerAim(bool bInView);
	bool ToggleMainMenu();
	bool TogglePlayerMenu();
	UFUNCTION(BlueprintCallable)
	bool OpenDeathWidget(bool bOpen);
	UFUNCTION(BlueprintCallable)
	bool OpenStartMenuWidget(bool bOpen);
	UFUNCTION(BlueprintCallable)
	void OpenLoadSaveGame(bool bOpen);
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UPackageUserWidget* PackageUI;
	UPROPERTY()
	UMenuUserWidget* MenuUserWidget;
	UPROPERTY()
	UPlayerUserWidget* PlayerUserWidget;
	UPROPERTY()
	UDeathUserWidget* DeathUserWidget;
	UPROPERTY()
	UStartMenuUserWidget* StartMenuUserWidget;
	UPROPERTY()
	ULoadSaveUserWidget* LoadSaveUserWidget;
	
public:
	UPackageUserWidget* GetPackageUserWidget() const;
	UMenuUserWidget* GetMenuUserWidget() const;
	UPlayerUserWidget* GetPlayerUserWidget() const;
	UDeathUserWidget* GetDeathUserWidget() const;
	
};
