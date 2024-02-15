// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon.h"
#include "CloseInWeapon.generated.h"

/**
 * 
 */
UCLASS()
//近战类型武器
class MYRPGGAME_API ACloseInWeapon : public AWeapon
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void TryToAttack() override;
	virtual void StopAttack() override;
	virtual void TrySettlementAttack(float Damage) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="LineTrace")
	TArray<FName> SocketNames;
	UPROPERTY()
	TArray<FHitResult> HitResults;
	UPROPERTY()
	TArray<FHitResult> SavedResults;
	UPROPERTY()
	TArray<FTransform> SocketTransform;
	UPROPERTY()
	TArray<AActor*> HitActors;
	bool bAttack;
public:
	FTimerHandle WeaponTimerHandle;

public:
	void HideWeapon(bool Out_State);
	void InitSocketTransForm();
	bool TryUpdateTransform();
	void TimeFunction();
	void GainDamage(AActor* Actor);
	UFUNCTION()
	void StartAttack();
	UFUNCTION()
	//用于结算攻击的角色
	void SettlementAttack(float Damage);
	UFUNCTION()
	void EndAttack();
	
	FTransform GetSocketTransform(FName SocketName);
};


