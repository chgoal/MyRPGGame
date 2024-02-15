// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

class UMyRPGSaveGame;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<FName> DestroyedActors;
protected:
	
public:
	UPROPERTY()
	TArray<UMyRPGSaveGame*> SaveGames;
	bool Check_ifDestroyed(FName Item);
	void DestroyItem(FName ItemID);
	void GetDestroyedActors(TArray<FName>& ActorsID);
};
