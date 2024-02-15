// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/CustomGameInstance.h"

bool UCustomGameInstance::Check_ifDestroyed(FName Item)
{
	return DestroyedActors.Find(Item)>-1;
}

void UCustomGameInstance::DestroyItem(FName ItemID)
{
	DestroyedActors.AddUnique(ItemID);
}

void UCustomGameInstance::GetDestroyedActors(TArray<FName>& ActorsID)
{
	ActorsID = DestroyedActors;
}
