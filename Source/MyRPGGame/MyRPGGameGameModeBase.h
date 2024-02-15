// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyRPGGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API AMyRPGGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyRPGGameGameModeBase();
	UFUNCTION(BlueprintCallable)
	void LoadGame();
};
