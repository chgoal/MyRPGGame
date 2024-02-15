// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/WeaponSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGame/MyRPGSaveGame.h"

void UWeaponSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	MaxWeapon = 0;
	MaxProps = 0;
	MaxSkin = 0;
	WeaponDataTable = LoadObject<UDataTable>(this,TEXT("DataTable'/Game/Projecte/Data/DataTable/DT_Weapon.DT_Weapon'"));
	PropsDataTable = LoadObject<UDataTable>(this,TEXT("DataTable'/Game/Projecte/Data/DataTable/DT_Props.DT_Props'"));
	SkinDataTable = LoadObject<UDataTable>(this,TEXT("DataTable'/Game/Projecte/Data/DataTable/DT_Skin.DT_Skin'"));
	MaxWeapon = AddTableToMap<FWeapons*>(WeaponDataTable,WeaponMap);
	MaxProps = AddTableToMap<FProps*>(PropsDataTable,PropsMap);
	MaxSkin = AddTableToMap<FSkin*>(SkinDataTable,SkinMap);
	LoadSaveGames();
}

int32 UWeaponSubsystem::GetMaxWeapon() const
{
	return MaxWeapon;
}

int32 UWeaponSubsystem::GetMaxSkin() const
{
	return MaxSkin;
}

int32 UWeaponSubsystem::GetMaxProps() const
{
	return MaxProps;
}

const FPropsBase* UWeaponSubsystem::GetWeaponsByID(int32 ID)
{
	if (WeaponMap.Contains(ID))
	{
		return WeaponMap[ID];
	}
	return nullptr;
}

const FPropsBase* UWeaponSubsystem::GetPropsByID(int32 ID)
{
	if (PropsMap.Contains(ID))
	{
		return PropsMap[ID];
	}
	return nullptr;
}

const FPropsBase* UWeaponSubsystem::GetSkinByID(int32 ID)
{
	if (SkinMap.Contains(ID))
	{
		return SkinMap[ID];
	}
	return nullptr;
}

const FPropsBase* UWeaponSubsystem::GetItemByIDAndType(int32 ID, EItemType Type)
{
	if (Type == EItemType::EPT_Weapon)
	{
		return GetWeaponsByID(ID);
	}
	 if (Type == EItemType::EPT_Tool)
	{
		return GetPropsByID(ID);
	}
	if (Type == EItemType::EPT_Skin)
	{
		return GetSkinByID(ID);
	}
	return nullptr;
}

const FPropsBase* UWeaponSubsystem::GetItemByIDAndType(FIDAndType IDAndType)
{
	return GetItemByIDAndType(IDAndType.ID,IDAndType.ItemType);
}

bool UWeaponSubsystem::Check_IfDestroyed(FName ItemID)
{
	return DestroyedActors.Find(ItemID)>-1;
}


void UWeaponSubsystem::DestroyItem(FName ItemID)
{
	DestroyedActors.AddUnique(ItemID);
}

void UWeaponSubsystem::GetDestroyedActors(TArray<FName>& ActorsID)
{
	ActorsID = DestroyedActors;
}
void UWeaponSubsystem::LoadSaveGames()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("MyGameSlot"),0))
	{
		if (UMyRPGSaveGame* MyRPGSaveGame = Cast<UMyRPGSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyGameSlot"),0)))
		{
			AddSaveGames(MyRPGSaveGame);
		}
	}
}

void UWeaponSubsystem::AddSaveGames(UMyRPGSaveGame* SaveGame)
{
	if (SaveGame)
	{
		if (SaveGames.Contains(FName(*SaveGame->SlotName)))
		{
			SaveGames.Emplace(FName(*SaveGame->SlotName),SaveGame);
		}
		else
		{
			SaveGames.Add(FName(*SaveGame->SlotName),SaveGame);
		}
	}
	
}

void UWeaponSubsystem::GetSaveGames(TMap<FName,UMyRPGSaveGame*>& T_SaveGames)
{
	T_SaveGames = SaveGames;
}

void UWeaponSubsystem::SetSelectSaveGame(UMyRPGSaveGame* MyRPGSaveGame)
{
	SelectSaveGame = MyRPGSaveGame;
	if (SelectSaveGame)
	{
		DestroyedActors = SelectSaveGame->DestroyedActors;
	}
}

void UWeaponSubsystem::ClearSelectSaveGame()
{
	SelectSaveGame = nullptr;
}

UMyRPGSaveGame* UWeaponSubsystem::GetSelectSaveGame()
{
	return SelectSaveGame;
}

template <typename T>
int32 UWeaponSubsystem::AddTableToMap(UDataTable* Table, TMap<int32, T>& Map)
{
	const TMap<FName,uint8*> Data = Table->GetRowMap();
	int32 MaxNum = 0;
	for (auto Item:Data)
	{
		int32 ID = 0;
		FString SLeft,SRight;
		if (Item.Key.ToString().Split(TEXT("_"),&SLeft,&SRight))
		{
			ID = FCString::Atoi(*SRight)+1;
		}
		else
		{
			ID = 0;
		}
		if (!Map.Contains(ID))
		{
			Map.Add(ID,reinterpret_cast<T>(Item.Value));
			MaxNum = MaxNum+1;
		}
	}
	return MaxNum;
}
