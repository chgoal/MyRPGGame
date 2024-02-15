// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaponSubsystem.generated.h"

class UWeaponAttributeSet;
struct FGameplayTag;
class USkinDataAsset;
class UPropsDataAsset;
class UWeaponDataAsset;
class UMyRPGSaveGame;
class AWeapon;
/**
 * 
 */
UENUM(BlueprintType)
//角色装备的武器大类
enum class EWeaponState : uint8
{
	EWS_None,//无武器
	EWS_Knight,//刀
	EWS_Spear,//长枪
	EWS_Gun,//远程类武器
};

UENUM()
//场景道具大类
enum class EItemType : uint8
{
	EPT_Tool,
	EPT_Skin,
	EPT_Weapon,
};

UENUM()
//装备栏大类
enum class ESkinType : uint8
{
	EST_NONE=0,
	EST_Bag,
	EST_Helment,//头盔
	EST_Armour,//盔甲
	EST_Leggings,//护腿
};

UENUM()
//道具作用大类
enum class EPropsType : uint8
{
	EPT_None,
	EPT_Blood,
	EPT_Energy,
	EPT_Attack,
	EPT_Defence,
	EPT_Sustain,//持续回血,
};

UENUM(BlueprintType)
enum class EQuickUse : uint8
{
	EQU_None,
	EQU_QuickUse1,
	EQU_QuickUse2
};

USTRUCT()
//道具武器等的基础信息
struct FPropsBase:public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	int32 ID;
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	EItemType ItemType;
	UPROPERTY(EditAnywhere)
	FString description;
};

USTRUCT()
//道具类别
struct FProps : public FPropsBase 
{
	GENERATED_BODY()
	FProps(): StaticMesh(nullptr), SkeletalMesh(nullptr), PropsType()
	{
		ItemType = EItemType::EPT_Tool;
	}

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	EPropsType PropsType;
	UPROPERTY(EditAnywhere)
	//保存一些道具的属性
	TSubclassOf<UPropsDataAsset> DataAsset;
	UPROPERTY(EditAnywhere,Category="PropsGA")
	TSubclassOf<class UGameplayAbility> AddPropsGameAbility;
};

USTRUCT()
//武器大类
struct FWeapons : public FPropsBase
{
	GENERATED_BODY()
	FWeapons(): WeaponIcon(nullptr), SkeletalMesh(nullptr), StaticMesh(nullptr), WeaponState()
	{
		ItemType = EItemType::EPT_Weapon;
	}

	UPROPERTY(EditAnywhere)
	UTexture2D* WeaponIcon;
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	EWeaponState WeaponState;
	UPROPERTY(EditAnywhere,Category="RightHand")
	FName MainSocketName;
	UPROPERTY(EditAnywhere,Category="RightHand")
	//右手武器
	TSubclassOf<AWeapon> MainWeaponActor;
	UPROPERTY(EditAnywhere,Category="LeftHand")
	FName OffSocketName;
	UPROPERTY(EditAnywhere,Category="LeftHand")
	//左手武器
	TSubclassOf<AWeapon> OffWeaponActor;
	UPROPERTY(EditAnywhere,Category="WeaponAsset")
	//武器对应的武器信息
	TSubclassOf<UWeaponDataAsset> DataAsset;
	UPROPERTY(EditAnywhere,Category="WeaponGA")
	TSubclassOf<class UGameplayAbility> AddWeaponsGameAbility;
	UPROPERTY(EditAnywhere,Category="WeaponGA")
	TSubclassOf<class UGameplayAbility> RemoveWeaponsGameAbility;
	
};

USTRUCT()
//NPC的武器
struct FNPCWeapon : public FPropsBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	EWeaponState WeaponState;
	UPROPERTY(EditAnywhere,Category="RightHand")
	FName MainSocketName;
	UPROPERTY(EditAnywhere,Category="RightHand")
	//右手武器
	TSubclassOf<AWeapon> MainWeaponActor;
	UPROPERTY(EditAnywhere,Category="LeftHand")
	FName OffSocketName;
	UPROPERTY(EditAnywhere,Category="LeftHand")
	//左手武器
	TSubclassOf<AWeapon> OffWeaponActor;
	UPROPERTY(EditAnywhere,Category="WeaponAsset")
	//武器对应的武器信息
	TSubclassOf<UWeaponDataAsset> DataAsset;
	
};

USTRUCT()
//皮肤防具大类
struct FSkin : public FPropsBase
{
	GENERATED_BODY()
	FSkin()
	{
		ItemType = EItemType::EPT_Skin;
		SkinType = ESkinType::EST_Armour; //默认为盔甲
	}

	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> StaticMeshes;
	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> SkeletalMeshes;
	UPROPERTY(EditAnywhere)
	//SkeltalMesh或者StaticMesh需要放入的Socket口
	FName Socket;
	UPROPERTY(EditAnywhere,Category="SkinType")
	ESkinType SkinType;
	UPROPERTY(EditAnywhere,Category="SkinAsset")
	TSubclassOf<USkinDataAsset> DataAsset;
};

USTRUCT(BlueprintType)
//背包中的内容同时保存ID和Type类型
struct FIDAndType
{
	GENERATED_BODY()
	FIDAndType():ID(0),ItemType(EItemType::EPT_Tool),Number(1){};
	FIDAndType(int32 Out_ID,EItemType Out_ItemType) :Number(0)
	{
		ID = Out_ID;
		ItemType = Out_ItemType;
	};
	FIDAndType(int32 Out_ID):Number(0)
	{
		ID = Out_ID;
		ItemType = EItemType::EPT_Tool;
	}
	UPROPERTY()
	int32 ID;
	UPROPERTY()
	EItemType ItemType;
	UPROPERTY()
	int32 Number;
};

USTRUCT(BlueprintType)
//武器的信息
struct FWeaponMsg
{
	GENERATED_BODY()
	explicit FWeaponMsg(): ID(-1), Attack(0), Defence(0), MaxBullet(0), CurrentBullet(0), GroupBullet(0),bEquip(false)
	{
	};
	
	//武器ID
	UPROPERTY()
	int32 ID;
	UPROPERTY()
	float Attack;
	UPROPERTY()
	float Defence;
	UPROPERTY()
	float MaxBullet;
	UPROPERTY()
	float CurrentBullet;
	UPROPERTY()
	float GroupBullet;
	UPROPERTY()
	bool bEquip;
};

USTRUCT(BlueprintType)
//道具的信息
struct FPropsMsg
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
//防具的信息
struct FSkinMsg
{
	GENERATED_BODY()
	FSkinMsg(): ID(0), NumberOfUse(0)
	{
	};
	int32 ID;
	int32 NumberOfUse;
	
};

UCLASS()
class MYRPGGAME_API UWeaponSubsystem : public UGameInstanceSubsystem//是一个单例模式
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	UPROPERTY()
	UDataTable* WeaponDataTable;
	UPROPERTY()
	UDataTable* PropsDataTable;
	UPROPERTY()
	UDataTable* SkinDataTable;
	int32 MaxWeapon;
	int32 MaxSkin;
	int32 MaxProps;
	int32 MaxNPCWeapon;
	TMap<int32,FWeapons*> WeaponMap;
	TMap<int32,FProps*> PropsMap;
	TMap<int32,FSkin*> SkinMap;

	//保存游戏部分
	UPROPERTY()
	TArray<FName> DestroyedActors;
	UPROPERTY()
	TMap<FName,UMyRPGSaveGame*> SaveGames;
	UPROPERTY()
	UMyRPGSaveGame* SelectSaveGame;
public:
	int32 GetMaxWeapon() const;
	int32 GetMaxSkin() const;
	int32 GetMaxProps() const;
	template<typename T>
	int32 AddTableToMap(UDataTable* Table,TMap<int32,T>& Map);
	const FPropsBase* GetWeaponsByID(int32 ID);
	const FPropsBase* GetPropsByID(int32 ID);
	const FPropsBase* GetSkinByID(int32 ID);


	const FPropsBase* GetItemByIDAndType(int32 ID,EItemType Type);
	const FPropsBase* GetItemByIDAndType(FIDAndType IDAndType);

	//保存游戏部分
	bool Check_IfDestroyed(FName ItemID);
	void DestroyItem(FName ItemID);
	void GetDestroyedActors(TArray<FName>& ActorsID);
	void LoadSaveGames();
	void AddSaveGames(UMyRPGSaveGame* SaveGame);
	void GetSaveGames(TMap<FName,UMyRPGSaveGame*>& T_SaveGames);
	void SetSelectSaveGame(UMyRPGSaveGame* MyRPGSaveGame);
	void ClearSelectSaveGame();
	UMyRPGSaveGame* GetSelectSaveGame();
};






