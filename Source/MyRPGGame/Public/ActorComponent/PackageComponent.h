// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystem/WeaponSubsystem.h"
#include "PackageComponent.generated.h"


class ASceneItem;
DECLARE_MULTICAST_DELEGATE(NotifyRemoveAll)
DECLARE_MULTICAST_DELEGATE_OneParam(NotifySceneItem,ASceneItem*)
DECLARE_MULTICAST_DELEGATE_TwoParams(NotifyPackageItem,int32,FIDAndType)
DECLARE_MULTICAST_DELEGATE_TwoParams(NotifySkin,ESkinType,int32);//Type,ID
DECLARE_MULTICAST_DELEGATE_OneParam(NotifyEquipWeapon,FWeaponMsg)
DECLARE_MULTICAST_DELEGATE_TwoParams(NotifyWeaponAdded,int32,FWeaponMsg)
DECLARE_MULTICAST_DELEGATE_TwoParams(NotifyWeaponExChanged,int32,int32)
DECLARE_MULTICAST_DELEGATE_ThreeParams(NotifyPropsBound,EQuickUse,int32,int32)//Key,Site,ID



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPGGAME_API UPackageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPackageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//检测周围东西
	void AddNearItem(ASceneItem* SceneItem);
	void RemoveNearItem(ASceneItem* SceneItem);
	
	//添加周围物品到背包中
	void AddItemToPackage(ASceneItem* SceneItem);
	void AddItemToPackage(FIDAndType IDAndType);
	void RemoveItemFromPackage(int32 Site,bool SpawnActor = true);

	//穿脱装备
	void PutinSkin(ASceneItem* SceneItem,ESkinType SkinType = ESkinType::EST_NONE);
	void PutinSkinFromPackage(int32 Site,ESkinType SkinType = ESkinType::EST_NONE);
	void PutinSkin(int32 ID,ESkinType SkinType = ESkinType::EST_NONE);
	void TakeOffSkin(ESkinType SkinType,bool bUpdateSkin = true);//updateSkin是确定是否更新装备
	void TakeOffSkinToWorld(ESkinType SkinType,bool bUpdateSkin = true);

	//穿脱武器
	void AddWeaponToPackage(int32 Site,ASceneItem* SceneItem);
	void AddWeaponToPackage(int32 Site,FWeaponMsg WeaponMsg);
	void RemoveWeaponFromPackage(int32 Site);
	void EquipWeapon(FWeaponMsg WeaponMsg);
	void UnEquipWeapon(bool bUpdate);
	void ExchangeWeapon(int32 Site1,int32 Site2);
	//void RemoveWeaponFromPackage(int32 Site)
	//void DiscardWeapon();
	//void ExChangeWeapon();
	//使用道具
	void UseProps(int32 Site);
	void UseProps(EQuickUse QuickUse);
	void AddPropsToSocket(EQuickUse QuickUse,int32 Site);
	void RemovePropsFromSocket(EQuickUse QuickUse);
	void PropsSocketExChange(EQuickUse QuickUse1,EQuickUse QuickUse2);

	//获取空余的Site
	int32 GetFreeSite() const;
	bool TryFindSite(FIDAndType IDAndType);
	int32 FindSite(FIDAndType IDAndType);

	void SpawnNearSceneItem(FIDAndType IDAndType) const;
	void SpawnNearSceneItem(FWeaponMsg WeaponMsg) const;
	
	//暴露给外边的参数
	bool GetNearItem(TArray<ASceneItem*>& NItem) const;
	bool GetPackageItem(TMap<int32,FIDAndType>& PItem) const;
	bool GetSkinMap(TMap<ESkinType,int32>& Map) const;
	bool GetPropsMap(TMap<EQuickUse,int32>& Map) const;
	bool GetWeaponMap(TMap<int32,FWeaponMsg>& Map) const;
	FIDAndType GetPackageItemFromSite(int32 Site);
	int32 GetSiteFromPropsMap(EQuickUse QuickUse);
	int32 GetIDFromSkinMap(ESkinType SKinType);
	FWeaponMsg GetMsgFromWeaponMap(int32 Site);
	EQuickUse GetQuickUseFromPropsMap(int32 Site);


	//存档加载
	bool LoadPackage(const TMap<int32,FIDAndType>& packageItem, const TMap<ESkinType,int32>& SkinMapItem, const TMap<EQuickUse,int32>& PropsMapItem, const TMap<int32,FWeaponMsg>& WeaponMapItem);
	void RemoveAllInPackage();
	void RemoveAllInSkinMap();
	void RemoveAllInPropsMap();
	void RemoveAllInWeaponMap();
	void ClearPackage();
	
	//测试用
	UFUNCTION(Exec)
	void PrintPackageItem();
protected:
	UPROPERTY(SaveGame)
	//存储附近武器
	TArray<ASceneItem*> NearItem;
	UPROPERTY(SaveGame)
	//背包中的信息
	TMap<int32,FIDAndType> Package;
	UPROPERTY(SaveGame)
	TMap<ESkinType,int32> SkinMap;
	UPROPERTY(SaveGame)
	TMap<EQuickUse,int32> PropsMap;//存储快捷键和背包中Site值
	UPROPERTY(SaveGame)
	TMap<int32,FWeaponMsg> WeaponMap;//Site,用于确定在背包UI中的哪一行,FWeaponMsg包含左右手武器以及武器的数据信息
public:
	//广播代理通知
	//附近有道具进入
	NotifySceneItem OnNearItemEnter;
	//附近道具离开
	NotifySceneItem OnNearItemLeave;

	NotifyPackageItem OnPackageItemAdded;
	//背包中有道具加入
	NotifyPackageItem OnPackageItemRemove;
	//背包中道具离开

	//穿上装备
	NotifySkin OnSkinPuton;
	//脱下装备
	NotifySkin OnSkinTakeOff;

	//装备武器主要链接装备组件
	NotifyEquipWeapon OnWeaponEquip;
	//卸载武器
	NotifyEquipWeapon OnWeaponUnEquip;

	//背包中加入武器
	NotifyWeaponAdded OnWeaponAdded;
	//背包中移除武器
	NotifyWeaponAdded OnWeaponRemoved;
	//交换背包中的武器
	NotifyWeaponExChanged OnWeaponExChanged;//规定有一个为-1时为空
	

	//道具绑定添加
	NotifyPropsBound OnPropsBoundAdded;
	//道具绑定去除
	NotifyPropsBound OnPropsBoundRemove;
	//交换
	// NotifyPropsBoundExchange OnPropsExChange;

	NotifyRemoveAll OnItemRemoveAll;
	NotifyRemoveAll OnWeaponRemoveAll;
	NotifyRemoveAll OnSkinRemoveAll;
	NotifyRemoveAll OnPropsRemoveAll;
	
};



inline EQuickUse UPackageComponent::GetQuickUseFromPropsMap(int32 Site)
{
	for (auto Props:PropsMap)
	{
		if (Props.Value == Site)
		{
			return Props.Key;
		}
	}
	return EQuickUse::EQU_None;
}

inline bool UPackageComponent::GetNearItem(TArray<ASceneItem*>& Item) const
{
	Item = NearItem;
	return true;
}
inline bool UPackageComponent::GetPackageItem(TMap<int32, FIDAndType>& PItem) const
{
	PItem = Package;
	return true;
}
inline bool UPackageComponent::GetSkinMap(TMap<ESkinType, int32>& Map) const
{
	Map = SkinMap;
	return true;
}

inline bool UPackageComponent::GetPropsMap(TMap<EQuickUse, int32>& Map) const
{
	Map = PropsMap;
	return true;
}

inline bool UPackageComponent::GetWeaponMap(TMap<int32, FWeaponMsg>& Map) const
{
	Map = WeaponMap;
	return true;
}