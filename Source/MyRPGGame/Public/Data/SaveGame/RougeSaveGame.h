// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RougeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API URougeSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,Category = Basic)
	FString PlayerName;
	UPROPERTY(VisibleAnywhere,Category = Basic)
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere,Category = Basic)
	uint32 UserIndex;
	URougeSaveGame();
};
