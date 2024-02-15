// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystem/WeaponSubsystem.h"
#include "SkinComponent.generated.h"
USTRUCT()
struct FSkeletalMeshArray
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;//可能是skeletalMeshComp
	UPROPERTY()
	TArray<UStaticMeshComponent*> StaticMeshComponents;//可能是StaticMesh
	bool bIsSkeletalMesh;//用于记录是否有装备
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPGGAME_API USkinComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkinComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void PutinSkin(ESkinType SkinType,int32 ID);
	void TakeOffSkin(ESkinType SkinType,int32 ID);
	void TakeOffAllSkin();

	void PutinSkinSkeletalMesh(ESkinType SkinType,const FSkin* Skin);//用于穿装备
	void ClearSkinSkeletalMesh(ESkinType SkinType);

	void PutinSkinStaticMesh(ESkinType SkinType,const FSkin* Skin);
	void ClearSkinStaticMesh(ESkinType SkinType);

	void DeleteSkinMesh(ESkinType SkinType);//用于删除产生的所有的SkeletalMesh以及StaticMesh
//武器功能
	void EquipWeapon(FWeaponMsg WeaponMsg);
	void UnEquipWeapon(FWeaponMsg WeaponMsg);

	void EquipWeapon(TSubclassOf<AWeapon> Weapon,FName WeaponSocket,bool bMain=true);
	void UnEquipWeapon(bool bMain=true);
	void UnEquipWeapon();
	
	UFUNCTION(BlueprintCallable)
	void LaunchWeapon(bool bIsMainWeapon = true);
	UFUNCTION(BlueprintCallable)
	void SettlementWeapon(float Damage,bool bIsMainWeapon = true);
	UFUNCTION(BlueprintCallable)
	void StopWeapon(bool bIsMainWeapon = true);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	AWeapon* GetWeapon(bool bIsMain=true);
	// UFUNCTION(BlueprintCallable)
	// void ExChangeWeapon(bool );

protected:
	UPROPERTY()
	TMap<ESkinType,FSkeletalMeshArray> MultiSkeletalMeshMap;
	UPROPERTY(BlueprintReadOnly)
	AWeapon* MainWeapon;
	UPROPERTY(BlueprintReadOnly)
	AWeapon* OffWeapon;


	
};




