// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/RPGPlayerController.h"

#include "ActorComponent/PackageComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "GameInstance/CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyRPGGame/MyRPGGame.h"
#include "SaveGame/MyRPGSaveGame.h"

ARPGPlayerController::ARPGPlayerController()
{
	SlotName = TEXT("MyGameSlot");
}

FGenericTeamId ARPGPlayerController::GetGenericTeamId() const
{
	if (TeamColor == ETeamColor::ETC_Green)
	{
		return TeamID_Green;
	}
	if (TeamColor == ETeamColor::ETC_Yellow)
	{
		return TeamID_Yellow;
	}
	return TeamID_Red;
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	WeaponSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>();
}

void ARPGPlayerController::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName,0))
	{
		if (UMyRPGSaveGame* MyRPGSaveGame = Cast<UMyRPGSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0)))
		{
			RPGSaveGame = MyRPGSaveGame;
			SaveGameToSlot(RPGSaveGame);
		}
	}
	else
	{
		TSubclassOf<UMyRPGSaveGame> SaveGameClass= LoadClass<UMyRPGSaveGame>(nullptr,TEXT("Blueprint'/Game/Projecte/Data/SaveGame/BP_SaveGame.BP_SaveGame_C'"));
		if (UMyRPGSaveGame* MyRPGSaveGame = Cast<UMyRPGSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass)))
		{
			RPGSaveGame = MyRPGSaveGame;
			SaveGameToSlot(RPGSaveGame);
		}
		
	}
}

void ARPGPlayerController::SaveGameToSlot(UMyRPGSaveGame* T_RPGSaveGame)
{
	if (APlayerCharacter* T_Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FString NowTime;
        T_RPGSaveGame->SaveTime = UKismetMathLibrary::Now().ToString();
        T_RPGSaveGame->LevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
		T_RPGSaveGame->CharacterLevel = T_Player->GetCharacterLevel();
        T_RPGSaveGame->CharacterLocation = T_Player->GetActorLocation();
        T_RPGSaveGame->CharacterRotator = T_Player->GetActorRotation();
        T_RPGSaveGame->Health = T_Player->GetHealth();
        T_RPGSaveGame->Mana = T_Player->GetMana();
        T_RPGSaveGame->Stamina = T_Player->GetStamina();
        if (T_Player->GetPackageComponent())
        {
        	T_Player->GetPackageComponent()->GetPackageItem(T_RPGSaveGame->PackageItem);
        	T_Player->GetPackageComponent()->GetSkinMap(T_RPGSaveGame->SkinMapItem);
        	T_Player->GetPackageComponent()->GetPropsMap(T_RPGSaveGame->PropsMapItem);
        	T_Player->GetPackageComponent()->GetWeaponMap(T_RPGSaveGame->WeaponMapItem);
        }
		if (WeaponSubsystem)
        {
        	WeaponSubsystem->GetDestroyedActors(T_RPGSaveGame->DestroyedActors);
			WeaponSubsystem->AddSaveGames(T_RPGSaveGame);
        }
		if (OnReloadSaveGame.IsBound())
        {
			OnReloadSaveGame.Broadcast();
        }
        UGameplayStatics::AsyncSaveGameToSlot(T_RPGSaveGame,SlotName,T_RPGSaveGame->UserIndex);
	}
	
}

void ARPGPlayerController::LoadGame()
{
	if (UWeaponSubsystem* T_WeaponSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		if (T_WeaponSubsystem->GetSelectSaveGame())
		{
			if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
			{
				UMyRPGSaveGame* T_RPGSaveGame = T_WeaponSubsystem->GetSelectSaveGame();
				PlayerCharacter->LoadSave(T_RPGSaveGame);
			}
			//T_WeaponSubsystem->SetSelectSaveGame(nullptr);
		}
	}
}
