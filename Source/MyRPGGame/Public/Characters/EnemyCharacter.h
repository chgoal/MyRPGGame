// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/TargetInterface.h"
#include "MyRPGGame/Public/Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class AWeapon;
class ASceneActor;
class APatrolPoint;
class UBoxComponent;
class UBehaviorTree;
/**
 * 
 */

UCLASS()
class MYRPGGAME_API AEnemyCharacter : public ABaseCharacter,public ITargetInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	//组件
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UWidgetComponent* FindEnemy;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UDecalComponent* DecalComponent;
	// UPROPERTY(EditDefaultsOnly)
	// UStaticMeshComponent* WeaponComponent;
	// UPROPERTY(EditDefaultsOnly)
	// UStaticMeshComponent* BackWeaponComponent;
	//资源
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;
	UPROPERTY()
	UAimUserWidget* ActiveTargetWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAimUserWidget> TargetBarWidgetClass;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bLoseEnemy;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bLock;
	UPROPERTY(VisibleAnywhere)
	bool bRest;
	UPROPERTY(VisibleAnywhere)
	bool bEquip;
	UPROPERTY(VisibleAnywhere)
	int32 RandomNum;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool AnimPlay;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool bSit;
	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName;
	UPROPERTY(EditDefaultsOnly)
	FName BackWeaponSocketName;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> MainWeapon;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> OffWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	//巡逻点
	TArray<APatrolPoint*> PatrolPoints;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ASceneActor* SitActor;
	
public:
	//功能类函数
	virtual void Select() override;
	virtual void CancelSelect() override;
	virtual UAimUserWidget* GetTargetWidget() const override;
	void Initialize();
	void BeginInitialize();
	UFUNCTION(BlueprintCallable)
	void SetWeaponVisibility(EWeaponHide HideState);
	UFUNCTION(BlueprintCallable)
	void EquipWeapon();
	UFUNCTION(BlueprintCallable)
	void UnEquipWeapon();
	//Get Set
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UBehaviorTree* GetBehaviorTree();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetLock();
	UFUNCTION(BlueprintCallable)
	void SetLock(bool Out_Lock);
	UFUNCTION(BlueprintCallable)
	void SetRest(bool Out_bRest);
	UFUNCTION(BlueprintCallable)
	void SetRandomNum(int32 Out_RandomNum);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetAnimPlay();
	UFUNCTION(BlueprintCallable)
	void SetAnimPlay(bool Out_AnimPlay);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetSit();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetLoseEnemy();
	UFUNCTION(BlueprintCallable)
	void SetLoseEnemy(bool Out_LoseEnemy);
	UFUNCTION(BlueprintCallable)
	void SetSit(bool Out_Sit);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	ASceneActor* GetSceneActor();
	UFUNCTION(BlueprintCallable)
	void SetEquip(bool Out_Equip);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetEquip();
	

	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<APatrolPoint*> GetPatrolPoint();

	
	//绑定

	friend class UEnemyAnimInstance;
	friend class UBTTaskNode;
};
inline UBehaviorTree* AEnemyCharacter::GetBehaviorTree()
{
	return BehaviorTree;
}

inline bool AEnemyCharacter::GetLock()
{
	return bLock;
}

inline void AEnemyCharacter::SetLock(bool Out_Lock)
{
	bLock = Out_Lock;
}

inline void AEnemyCharacter::SetRest(bool Out_bRest)
{
	bRest = Out_bRest;
}

inline void AEnemyCharacter::SetRandomNum(int32 Out_RandomNum)
{
	RandomNum = Out_RandomNum;
}

inline bool AEnemyCharacter::GetAnimPlay()
{
	return AnimPlay;
}

inline void AEnemyCharacter::SetAnimPlay(bool Out_AnimPlay)
{
	AnimPlay = Out_AnimPlay;
}

inline bool AEnemyCharacter::GetSit()
{
	return bSit;
}

inline void AEnemyCharacter::SetSit(bool Out_Sit)
{
	bSit = Out_Sit;
}

inline TArray<APatrolPoint*> AEnemyCharacter::GetPatrolPoint()
{
	return PatrolPoints;
}
inline  ASceneActor* AEnemyCharacter::GetSceneActor()
{
	return SitActor;
}
inline bool AEnemyCharacter::GetLoseEnemy()
{
	return bLoseEnemy;
}
inline void AEnemyCharacter::SetLoseEnemy(bool Out_HasEnemy)
{
	bLoseEnemy = Out_HasEnemy;
}

inline void AEnemyCharacter::SetEquip(bool Out_Equip)
{
	bEquip = Out_Equip;
	
}
inline bool AEnemyCharacter::GetEquip()
{
	return bEquip;
}
