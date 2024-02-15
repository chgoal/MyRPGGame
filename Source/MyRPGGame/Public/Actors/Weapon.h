// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subsystem/WeaponSubsystem.h"
#include "Weapon.generated.h"

class ISkinInterface;
class ABaseCharacter;
UCLASS()
class MYRPGGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	//组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EWeaponState WeaponState;
	//UPROPERTY()//存储继承BaseCharacter类的指针
	ISkinInterface* MineSkinInterface;
	UPROPERTY(EditAnywhere,Category="WeaponMsg")
	FWeaponMsg WeaponMsg;
	UPROPERTY()
	int32 ID;//武器ID
	UPROPERTY()
	bool bIsMain;//用于记录是否为主手武器
	UPROPERTY()
	bool bEquip;//确定是否能装备
	UPROPERTY(EditAnywhere,Category="Attribute")
	float AttackPower;
public:
	UFUNCTION(BlueprintCallable)
	//写武器的开始和结束攻击的函数
	virtual void TryToAttack(){};
	UFUNCTION(BlueprintCallable)
	virtual void TrySettlementAttack(float Damage){};
	UFUNCTION(BlueprintCallable)
	virtual void StopAttack(){};
	UFUNCTION(BlueprintCallable,BlueprintPure)
	EWeaponState GetWeaponState();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetID();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FWeaponMsg GetWeaponMsg();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetbIsMain();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetbEquip();
	UFUNCTION(BlueprintCallable)
	void SetWeaponState(EWeaponState Out_WeaponState);
	UFUNCTION(BlueprintCallable)
	void SetID(int32 Out_ID);
	UFUNCTION(BlueprintCallable)
	void SetWeaponMsg(FWeaponMsg Out_WeaponMsg);
	UFUNCTION(BlueprintCallable)
	void SetbIsMain(bool Out_bIsMain);
	UFUNCTION(BlueprintCallable)
	void SetbEquip(bool Out_bEquip);
	UFUNCTION(BlueprintCallable)
	void SetReceiveDecals(bool bNewReceivesDecals);

	//功能性函数
	void WeaponSetMaster(ISkinInterface* SkinInterface,FName SocketName);
	void ClearMaster();
	virtual void HideWeapon(bool bVisibility);
	

};

inline void AWeapon::SetbEquip(bool Out_bEquip)
{
	bEquip = Out_bEquip;
}

inline void AWeapon::SetbIsMain(bool Out_bIsMain)
{
	bIsMain = Out_bIsMain;
}
