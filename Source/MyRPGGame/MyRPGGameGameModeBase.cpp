// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyRPGGameGameModeBase.h"

#include "Characters/BasePlayerState.h"
#include "Controller/RPGPlayerController.h"
#include "Public/Characters/PlayerCharacter.h"
#include "UMG/PlayerHUD.h"

AMyRPGGameGameModeBase::AMyRPGGameGameModeBase()
{
	DefaultPawnClass = LoadClass<APlayerCharacter>(GetWorld(),TEXT("Blueprint'/Game/Projecte/Blueprint/Character/BP_Player.BP_Player_C'"));
	//DefaultPawnClass = LoadClass<ACharacter>(GetWorld(),TEXT("Blueprint'/Game/Projecte/Blueprint/Character/BP_LoadPlayer.BP_LoadPlayer_C'"));
	HUDClass = APlayerHUD::StaticClass();
	PlayerStateClass = LoadClass<ABasePlayerState>(GetWorld(),TEXT("Blueprint'/Game/Projecte/Blueprint/PlayerState/BP_PlayerState.BP_PlayerState_C'"));
	PlayerControllerClass = ARPGPlayerController::StaticClass();
}

void AMyRPGGameGameModeBase::LoadGame()
{
	DefaultPawnClass = LoadClass<APlayerCharacter>(GetWorld(),TEXT("Blueprint'/Game/Projecte/Blueprint/Character/BP_Player.BP_Player_C'"));
}
