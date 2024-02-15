// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

class UWeaponSubsystem;
class UCustomGameInstance;
class UMyRPGSaveGame;
struct FGenericTeamId;
enum class ETeamColor : uint8;
DECLARE_MULTICAST_DELEGATE(NotifyReloadSaveGame)
/**
 * 
 */
UCLASS()
class MYRPGGAME_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARPGPlayerController();
	UPROPERTY(EditAnywhere)
	ETeamColor TeamColor;
	FGenericTeamId GetGenericTeamId() const;
	FString SlotName;
	UPROPERTY()
	UMyRPGSaveGame* RPGSaveGame;
	UPROPERTY()
	UWeaponSubsystem* WeaponSubsystem;

	//保存加载游戏
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	void SaveGameToSlot(UMyRPGSaveGame* T_RPGSaveGame);
	UFUNCTION(BlueprintCallable)
	void LoadGame();

	NotifyReloadSaveGame OnReloadSaveGame;
protected:
	virtual void BeginPlay() override;
};
