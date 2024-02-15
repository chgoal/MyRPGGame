// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Subsystem/WeaponSubsystem.h"
#include "MyRPGSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class MYRPGGAME_API UMyRPGSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString SlotName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString SaveTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 UserIndex;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FVector CharacterLocation;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FRotator CharacterRotator;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TMap<int32,FIDAndType> PackageItem;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TMap<ESkinType,int32> SkinMapItem;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TMap<EQuickUse,int32> PropsMapItem;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TMap<int32,FWeaponMsg> WeaponMapItem;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float Health;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float Mana;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite);
	float Stamina;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int32 CharacterLevel;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<FName> DestroyedActors;


	//初始化
	UMyRPGSaveGame();

	//判断不同
	//bool operator==(const UMyRPGSaveGame& MyRPGSaveGame);
};
