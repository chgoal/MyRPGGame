// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/PackageComponent.h"

#include "Actors/SceneItem.h"
#include "Characters/BaseCharacter.h"

// Sets default values for this component's properties
UPackageComponent::UPackageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPackageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPackageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPackageComponent::AddNearItem(ASceneItem* SceneItem)
{
	NearItem.Add(SceneItem);
	if (OnNearItemEnter.IsBound())
	{
		OnNearItemEnter.Broadcast(SceneItem);
	}
}

void UPackageComponent::RemoveNearItem(ASceneItem* SceneItem)
{
	if (NearItem.Contains(SceneItem))
	{
		NearItem.Remove(SceneItem);
		if (OnNearItemLeave.IsBound())
		{
			OnNearItemLeave.Broadcast(SceneItem);
		}
	}
}

void UPackageComponent::AddItemToPackage(ASceneItem* SceneItem)
{
	if (!SceneItem)
	{
		return;
	}
	if (SceneItem->GetItemType() == EItemType::EPT_Weapon)
	{
		return;
	}
	FIDAndType IDAndType;
	IDAndType.ID = SceneItem->GetID();
	IDAndType.ItemType = SceneItem->GetItemType();
	IDAndType.Number = SceneItem->GetNumber();//直接加,不是道具是不会显示的
	AddItemToPackage(IDAndType);
	SceneItem->PickUp();
}

void UPackageComponent::AddItemToPackage(FIDAndType IDAndType)
{
	int32 Site;
	if (IDAndType.ItemType == EItemType::EPT_Tool)
	{
		if (TryFindSite(IDAndType))//背包中有对应的IDAndType的话加数量
		{
			Site = FindSite(IDAndType);
			if (Package.Contains(Site))
			{
				Package[Site].Number = Package[Site].Number+IDAndType.Number;
				if (OnPackageItemAdded.IsBound())
				{
					OnPackageItemAdded.Broadcast(Site,Package[Site]);
				}
			}
		}
		else
		{
			Site = GetFreeSite();
			Package.Add(Site,IDAndType);
			if (OnPackageItemAdded.IsBound())
			{
				OnPackageItemAdded.Broadcast(Site,Package[Site]);
			}
		}
	}
	else
	{
		Site = GetFreeSite();
		Package.Add(Site,IDAndType);
		if (OnPackageItemAdded.IsBound())
		{
			OnPackageItemAdded.Broadcast(Site,Package[Site]);
		}
	}
}



void UPackageComponent::RemoveItemFromPackage(int32 Site,bool SpawnActor)
{
	if (!Package.Contains(Site))
	{
		return;
	}
	if (OnPackageItemRemove.IsBound())
	{
		OnPackageItemRemove.Broadcast(Site,Package[Site]);
	}
	if (SpawnActor)
	{
		SpawnNearSceneItem(Package[Site]);
	}
	Package.Remove(Site);
	
}

void UPackageComponent::PutinSkin(ASceneItem* SceneItem, ESkinType SkinType)
{
	if (!SceneItem)
	{
		return;
	}
	if (SceneItem->GetItemType()!=EItemType::EPT_Skin)
	{
		return;
	}
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetSkinByID(SceneItem->GetID());
	if (!PropsBase)
	{
		return;
	}
	if (PropsBase->ItemType!=EItemType::EPT_Skin)
	{
		return;
	}
	const FSkin* SkinInfo = static_cast<const FSkin*>(PropsBase);
	if (SkinType != ESkinType::EST_NONE)
	{
		if (SkinType != SkinInfo->SkinType)
		{
			return;
		}
	}
	SkinType = SkinInfo->SkinType;
	TakeOffSkin(SkinType,false);//脱下装备
	if (SkinMap.Contains(SkinType))
	{
		SkinMap[SkinType] = SceneItem->GetID();
	}
	else
	{
		SkinMap.Add(SkinType,SceneItem->GetID());
	}
	if (OnSkinPuton.IsBound())
	{
		OnSkinPuton.Broadcast(SkinType,SceneItem->GetID());
	}
	SceneItem->PickUp();
}

void UPackageComponent::PutinSkinFromPackage(int32 Site, ESkinType SkinType)
{
	if (!Package.Contains(Site))
	{
		return;
	}
	if (Package[Site].ItemType != EItemType::EPT_Skin)
	{
		return;
	}
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetSkinByID(Package[Site].ID);
	if (!PropsBase)
	{
		return;
	}
	if (PropsBase->ItemType!= EItemType::EPT_Skin)
	{
		return;
	}
	const FSkin* SkinInfo = static_cast<const FSkin*>(PropsBase);
	if (SkinType != ESkinType::EST_NONE)
	{
		if (SkinType != SkinInfo->SkinType)
		{
			return;
		}
	}
	SkinType = SkinInfo->SkinType;
	TakeOffSkin(SkinType,false);
	SkinMap.Add(SkinType,Package[Site].ID);
	if (OnSkinPuton.IsBound())
	{
		OnSkinPuton.Broadcast(SkinType,Package[Site].ID);
	}
	if (OnPackageItemRemove.IsBound())
	{
		OnPackageItemRemove.Broadcast(Site,Package[Site]);
	}
	Package.Remove(Site);
	
	
}

void UPackageComponent::PutinSkin(int32 ID, ESkinType SkinType)
{
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetSkinByID(ID);
	if (!PropsBase)
	{
		return;
	}
	if (PropsBase->ItemType!= EItemType::EPT_Skin)
	{
		return;
	}
	const FSkin* SkinInfo = static_cast<const FSkin*>(PropsBase);
	if (SkinType != ESkinType::EST_NONE)
	{
		if (SkinType != SkinInfo->SkinType)
		{
			return;
		}
	}
	SkinType = SkinInfo->SkinType;
	TakeOffSkin(SkinType,false);
	SkinMap.Add(SkinType,ID);
	if (OnSkinPuton.IsBound())
	{
		OnSkinPuton.Broadcast(SkinType,ID);
	}
}

void UPackageComponent::TakeOffSkin(ESkinType SkinType, bool bUpdateSkin)
{
	if (SkinMap.Contains(SkinType))
	{
		FIDAndType IDAndType;
		IDAndType.ID = SkinMap[SkinType];
		IDAndType.ItemType = EItemType::EPT_Skin;
		AddItemToPackage(IDAndType);
		if (bUpdateSkin)
		{
			if (OnSkinTakeOff.IsBound())
			{
				OnSkinTakeOff.Broadcast(SkinType,-1);
			}
		}
		SkinMap.Remove(SkinType);
	}
}

void UPackageComponent::TakeOffSkinToWorld(ESkinType SkinType, bool bUpdateSkin)
{
	if (!SkinMap.Contains(SkinType))
	{
		return;
	}
	if (SkinMap.Contains(SkinType))
	{
		FIDAndType IDAndType;
		IDAndType.ID = SkinMap[SkinType];
		IDAndType.ItemType = EItemType::EPT_Skin;
		if (bUpdateSkin)
		{
			if (OnSkinTakeOff.IsBound())
            {
            	OnSkinTakeOff.Broadcast(SkinType,-1);
            }
		}
		SpawnNearSceneItem(IDAndType);
		SkinMap.Remove(SkinType);
	}
}



void UPackageComponent::AddWeaponToPackage(int32 Site, ASceneItem* SceneItem)
{
	if (!SceneItem)
	{
		return;
	}
	if (SceneItem->GetItemType()!=EItemType::EPT_Weapon)
	{
		return;
	}
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetWeaponsByID(SceneItem->GetID());
	if (!PropsBase)
	{
		return;
	}
	const FWeapons* Weapons = static_cast<const FWeapons*>(PropsBase);
	if (!Weapons)
	{
		return;
	}
	FWeaponMsg WeaponMsg = SceneItem->GetWeaponMsg();
	WeaponMap.Add(Site,WeaponMsg);
	if (OnWeaponAdded.IsBound())
	{
		OnWeaponAdded.Broadcast(Site,WeaponMsg);
	}
	if (Site == 1)
	{
		UnEquipWeapon(true);
		EquipWeapon(WeaponMsg);
	}
	SceneItem->PickUp();
}
void UPackageComponent::AddWeaponToPackage(int32 Site, FWeaponMsg WeaponMsg)
{
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetWeaponsByID(WeaponMsg.ID);
	if (!PropsBase)
	{
		return;
	}
	const FWeapons* Weapons = static_cast<const FWeapons*>(PropsBase);
	if (!Weapons)
	{
		return;
	}
	WeaponMap.Add(Site,WeaponMsg);
	if (OnWeaponAdded.IsBound())
	{
		OnWeaponAdded.Broadcast(Site,WeaponMsg);
	}
	if (Site == 1)
	{
		UnEquipWeapon(true);
		EquipWeapon(WeaponMsg);
	}
}

void UPackageComponent::RemoveWeaponFromPackage(int32 Site)
{
	if (WeaponMap.Contains(Site))
	{
		if (OnWeaponRemoved.IsBound())
		{
			FWeaponMsg WeaponMsg;
			WeaponMsg.ID = -1;
			OnWeaponRemoved.Broadcast(Site,WeaponMsg);
		}
		SpawnNearSceneItem(WeaponMap[Site]);
		WeaponMap.Remove(Site);
		if (Site == 1 )
		{
			UnEquipWeapon(true);
		}
	}
	
}

void UPackageComponent::EquipWeapon(FWeaponMsg WeaponMsg)
{
	if (OnWeaponEquip.IsBound())
	{
		OnWeaponEquip.Broadcast(WeaponMsg);
	}
}
void UPackageComponent::UnEquipWeapon(bool bUpdate)
{
	if (bUpdate)
	{
		if (OnWeaponUnEquip.IsBound())
		{
			FWeaponMsg WeaponMsg;
			OnWeaponUnEquip.Broadcast(WeaponMsg);
		}
	}
}

void UPackageComponent::ExchangeWeapon(int32 Site1, int32 Site2)
{
	if (Site1 == Site2)
	{
		return;
	}
	if (!WeaponMap.Contains(Site1) && !WeaponMap.Contains(Site2))
	{
		return;
	}
	if(WeaponMap.Contains(Site1) && !WeaponMap.Contains(Site2))
	{
		WeaponMap.Add(Site2,WeaponMap[Site1]);
		WeaponMap.Remove(Site1);
	}
	else if (WeaponMap.Contains(Site2) && !WeaponMap.Contains(Site1))
	{
		WeaponMap.Add(Site1,WeaponMap[Site2]);
		WeaponMap.Remove(Site2);
	}
	else if (WeaponMap.Contains(Site1) && WeaponMap.Contains(Site2))//交换
	{
		FWeaponMsg WeaponMsg = WeaponMap[Site1];
		WeaponMap.Remove(Site1);
		WeaponMap.Add(Site1,WeaponMap[Site2]);
		WeaponMap.Remove(Site2);
		WeaponMap.Add(Site2,WeaponMsg);
	}
	if (OnWeaponExChanged.IsBound())
	{
		OnWeaponExChanged.Broadcast(Site1,Site2);
	}
	if (Site1 == 1 || Site2 == 1)
	{
		UnEquipWeapon(true);
		if (WeaponMap.Contains(1))
		{
			EquipWeapon(WeaponMap[1]);
		}
	}
}

void UPackageComponent::UseProps(int32 Site)
{
	if (Package.Contains(Site))
	{
		if (Package[Site].ItemType == EItemType::EPT_Tool)
		{
			Package[Site].Number = Package[Site].Number-1;
			if (OnPackageItemAdded.IsBound())
			{
				OnPackageItemAdded.Broadcast(Site,Package[Site]);
			}
			if (Package[Site].Number == 0)
			{
				RemovePropsFromSocket(GetQuickUseFromPropsMap(Site));
				RemoveItemFromPackage(Site,false);
			}
		}
	}
}

void UPackageComponent::UseProps(EQuickUse QuickUse)
{
	if (PropsMap.Contains(QuickUse))
	{
		UseProps(PropsMap[QuickUse]);
	}
}

void UPackageComponent::AddPropsToSocket(EQuickUse QuickUse,int32 Site)
{
	RemovePropsFromSocket(QuickUse);
	PropsMap.Add(QuickUse,Site);
	if (OnPropsBoundAdded.IsBound())
	{
		if (Package.Contains(Site))
		{
			OnPropsBoundAdded.Broadcast(QuickUse,Site,Package[Site].ID);
		}
	}
}

void UPackageComponent::RemovePropsFromSocket(EQuickUse QuickUse)
{
	if (PropsMap.Contains(QuickUse))
	{
		if (OnPropsBoundRemove.IsBound())
		{
			OnPropsBoundRemove.Broadcast(QuickUse,PropsMap[QuickUse],-1);
		}
		PropsMap.Remove(QuickUse);
	}
}
void UPackageComponent::PropsSocketExChange(EQuickUse QuickUse1, EQuickUse QuickUse2)
{
	if (!PropsMap.Contains(QuickUse1) && !PropsMap.Contains(QuickUse2))
	{
		return;
	}
	if (PropsMap.Contains(QuickUse1) && !PropsMap.Contains(QuickUse2))
	{
		PropsMap.Add(QuickUse2,PropsMap[QuickUse1]);
		RemovePropsFromSocket(QuickUse1);
		return;
	}
	if (!PropsMap.Contains(QuickUse1) && PropsMap.Contains(QuickUse2))
	{
		PropsMap.Add(QuickUse1,PropsMap[QuickUse2]);
		RemovePropsFromSocket(QuickUse2);
		return;
	}
	if (PropsMap.Contains(QuickUse1) && PropsMap.Contains(QuickUse2))
	{
		int32 TSite = PropsMap[QuickUse1];
		AddPropsToSocket(QuickUse1,PropsMap[QuickUse2]);
		AddPropsToSocket(QuickUse2,TSite);
		return;
	}
	
}


int32 UPackageComponent::GetFreeSite() const
{
	int32 Site = 0;
	while (Package.Contains(Site))
	{
		Site++;
	}
	return Site;
}

bool UPackageComponent::TryFindSite(FIDAndType IDAndType)
{
	if (FindSite(IDAndType) == -1)
	{
		return false;
	}
	return true;
}

int32 UPackageComponent::FindSite(FIDAndType IDAndType)
{
	int32 Site = 0;
	while (Package.Contains(Site))
	{
		if (Package[Site].ID == IDAndType.ID && Package[Site].ItemType == IDAndType.ItemType)
		{
			return Site;
		}
		Site++;
	}
	return -1;
}

void UPackageComponent::SpawnNearSceneItem(FIDAndType IDAndType) const
{
	if (const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwner()))
	{
		FTransform Trans;
		Trans.SetLocation(BaseCharacter->GetActorLocation()+FRotator(0.f,FMath::RandRange(0.f,360.f),0.f).Vector()*FMath::RandRange(50.f,100.f));
		ASceneItem* SceneItem = BaseCharacter->GetWorld()->SpawnActorDeferred<ASceneItem>(ASceneItem::StaticClass(),Trans);
		SceneItem->SetID(IDAndType.ID);
		SceneItem->SetPropsType(IDAndType.ItemType);
		SceneItem->SetNumber(IDAndType.Number);
		SceneItem->SetbThrow(true);
		SceneItem->FinishSpawning(Trans);
	}
}
void UPackageComponent::SpawnNearSceneItem(FWeaponMsg WeaponMsg) const
{
	if (const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwner()))
	{
		FTransform Trans;
		Trans.SetLocation(BaseCharacter->GetActorLocation()+FRotator(0.f,FMath::RandRange(0.f,360.f),0.f).Vector()*FMath::RandRange(50.f,100.f));
		ASceneItem* SceneItem = BaseCharacter->GetWorld()->SpawnActorDeferred<ASceneItem>(ASceneItem::StaticClass(),Trans);
		SceneItem->SetID(WeaponMsg.ID);
		SceneItem->SetPropsType(EItemType::EPT_Weapon);
		SceneItem->SetWeaponMsg(WeaponMsg);
		SceneItem->SetbThrow(true);
		SceneItem->FinishSpawning(Trans);
	}
}

FIDAndType UPackageComponent::GetPackageItemFromSite(int32 Site)
{
	if (Package.Contains(Site))
	{
		return Package[Site];
	}
	return FIDAndType(-1);
}

int32 UPackageComponent::GetSiteFromPropsMap(EQuickUse QuickUse)
{
	if (PropsMap.Contains(QuickUse))
	{
		return PropsMap[QuickUse];
	}
	return -1;
}

int32 UPackageComponent::GetIDFromSkinMap(ESkinType SKinType)
{
	if (SkinMap.Contains(SKinType))
	{
		return SkinMap[SKinType];
	}
	return -1;
}

FWeaponMsg UPackageComponent::GetMsgFromWeaponMap(int32 Site)
{
	FWeaponMsg WeaponMsg;
	if (WeaponMap.Contains(Site))
	{
		return WeaponMap[Site];
	}
	return WeaponMsg;
}

bool UPackageComponent::LoadPackage(const TMap<int32, FIDAndType>& PackageItem, const TMap<ESkinType, int32>& SkinMapItem,
                                    const TMap<EQuickUse, int32>& PropsMapItem, const TMap<int32, FWeaponMsg>& WeaponMapItem)
{
	ClearPackage();
	for (auto Item: PackageItem)
	{
		AddItemToPackage(Item.Value);
	}
	for (auto Item:WeaponMapItem)
	{
		AddWeaponToPackage(Item.Key,Item.Value);
	}
	for (auto Item : SkinMapItem)
	{
		PutinSkin(Item.Value,Item.Key);
	}
	for (auto Item: PropsMapItem)
	{
		AddPropsToSocket(Item.Key,Item.Value);
	}
	return true;
}

void UPackageComponent::RemoveAllInPackage()
{
	Package.Empty();
	if (OnItemRemoveAll.IsBound())
	{
		OnItemRemoveAll.Broadcast();
	}
}

void UPackageComponent::RemoveAllInSkinMap()
{
	SkinMap.Empty();
	if (OnSkinRemoveAll.IsBound())
	{
		OnSkinRemoveAll.Broadcast();
	}
}

void UPackageComponent::RemoveAllInPropsMap()
{
	PropsMap.Empty();
	if (OnPropsRemoveAll.IsBound())
	{
		OnPropsRemoveAll.Broadcast();
	}
}

void UPackageComponent::RemoveAllInWeaponMap()
{
	WeaponMap.Empty();
	if (OnWeaponRemoveAll.IsBound())
	{
		OnWeaponRemoveAll.Broadcast();
	}
}

void UPackageComponent::ClearPackage()
{
	
	RemoveAllInWeaponMap();
	RemoveAllInPropsMap();
	RemoveAllInSkinMap();
	RemoveAllInPackage();
}

void UPackageComponent::PrintPackageItem()
{
	UE_LOG(LogTemp, Log, TEXT("PrintPackageItem"))
	for (auto Item:Package)
	{
		UE_LOG(LogTemp, Log, TEXT("Item.Key = %d,Item.Value.Number=%d"),Item.Key,Item.Value.Number)
	}
}















