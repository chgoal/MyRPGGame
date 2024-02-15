// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subsystem/WeaponSubsystem.h"
#include "SceneItem.generated.h"

UCLASS()
class MYRPGGAME_API ASceneItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BgSpawn();
	UFUNCTION(BlueprintImplementableEvent)
	void DelayDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//这里重载一些virtual函数
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	//基础组件
	UPROPERTY(EditAnywhere)
	UBillboardComponent* BillboardComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(EditAnywhere,Category="BaseSet")
	//物品种类
	EItemType ItemType;
	UPROPERTY(EditAnywhere,Category="BaseSet")
	FName ActorID;
	UPROPERTY(EditAnywhere,Category="BaseSet")
	//显示的ID
	int32 ID;
	UPROPERTY(EditAnywhere,Category="Numbers")
	//如果是道具的话道具的个数
	int32 Number;
	UPROPERTY(EditAnywhere,Category="Random")
	//开启随机后ID和道具会进行随机分配
	bool bRandom;
	UPROPERTY(EditAnywhere,Category="Random")
	//开启后种类random
	bool bItemRandom;
	UPROPERTY(EditAnywhere,Category="Random")
	//最大数量
	int32 MaxNumber;
	UPROPERTY(EditAnywhere,Category="Random")
	//最小数量
	int32 MinNumber;
	UPROPERTY(VisibleAnywhere,Category="Numbers")
	//当前种类可以填写的最大ID值
	int32 MaxID;

	//一些简单的隐藏属性
	UPROPERTY()
	bool bThrow;//从背包中被扔出来的，需要保存使用记录
	UPROPERTY(VisibleAnywhere)
	FWeaponMsg WeaponMsg;//用于记录从背包中扔出的武器的信息

	FPropsMsg PropsMsg;
	

	//记录添加注册的组件
	UPROPERTY()
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	UPROPERTY()
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
public:
	//暴露给外面的函数
	UFUNCTION(BlueprintCallable,BlueprintPure)
	EItemType GetItemType();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetNumber();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetID();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FWeaponMsg GetWeaponMsg();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetbThrow();
	//设置的函数
	void SetID(int32 Out_ID);
	void SetNumber(int32 Out_Number);
	void SetPropsType(EItemType Out_ItemType);
	void SetWeaponMsg(FWeaponMsg Out_WeaponMsg);
	void SetbThrow(bool Out_bThrow);

	//功能型函数
	void InitActor();
	void RandomIDAndNumber();
	void RandomItem();
	void InitMaxID();
	void PickUp();
	UStaticMeshComponent* GetStaticComponent();
	USkeletalMeshComponent* GetSkeletalMeshComponent();
	UStaticMeshComponent* NewStaticMeshComponent();
	USkeletalMeshComponent* NewSkeletalMeshComponent();
	
};
