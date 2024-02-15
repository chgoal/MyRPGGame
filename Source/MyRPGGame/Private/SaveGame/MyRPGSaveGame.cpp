// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/MyRPGSaveGame.h"

UMyRPGSaveGame::UMyRPGSaveGame()
{
	SlotName = TEXT("MyGameSlot");
}

// bool UMyRPGSaveGame::operator==(const UMyRPGSaveGame& MyRPGSaveGame)
// {
// 	if (SlotName == MyRPGSaveGame.SlotName &&
// 		SaveTime == MyRPGSaveGame.SaveTime &&
// 		UserIndex == MyRPGSaveGame.UserIndex &&
// 		LevelName == MyRPGSaveGame.LevelName &&
// 		CharacterLocation == MyRPGSaveGame.CharacterLocation &&
// 		CharacterRotator == MyRPGSaveGame.CharacterRotator &&
// 		PackageItem.OrderIndependentCompareEqual(MyRPGSaveGame.PackageItem) &&
// 		SkinMapItem.OrderIndependentCompareEqual(MyRPGSaveGame.SkinMapItem) &&
// 		PropsMapItem.OrderIndependentCompareEqual(MyRPGSaveGame.PropsMapItem) &&
// 		WeaponMapItem.OrderIndependentCompareEqual(MyRPGSaveGame.WeaponMapItem) &&
// 		Health == MyRPGSaveGame.Health &&
// 		Mana == MyRPGSaveGame.Mana &&
// 		Stamina == MyRPGSaveGame.Stamina &&
// 		CharacterLevel == MyRPGSaveGame.CharacterLevel &&
// 		DestroyedActors == MyRPGSaveGame.DestroyedActors
// 		)
// 	{
// 		return true;
// 	}
// 	return false;
// }
