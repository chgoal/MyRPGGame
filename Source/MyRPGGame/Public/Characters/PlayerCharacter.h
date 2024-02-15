// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyRPGGame/Public/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
protected:
	virtual void BeginPlay() override;
public:
	//继承的虚函数
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual FVector GetPawnViewLocation() const override;
	virtual void LoadSave(USaveGame* SaveGame) override;

public:
	//写函数
	void UseProps(int32 Site);//使用道具,Site是背包中的位置
	void UseProps(EQuickUse QuickUse);
	//UFUNCTION绑定类型的函数

	//操作映射或轴映射
	UFUNCTION()
	void LookUP(float Axis);
	UFUNCTION()
	void LookAround(float Axis);
	UFUNCTION()//用于平滑调整中键瞄准后的转身
	void LockRotator();
	// UFUNCTION()
	// void StartSprite();
	// UFUNCTION()
	// void StopSprite();
	UFUNCTION()
	void FirstQuickUse();
	UFUNCTION()
	void SecondQuickUse();
	
	

	//代理绑定
	UFUNCTION()
	void OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//普通并暴露给蓝图
	UFUNCTION()
	void TogglePackage();
	UFUNCTION()
	void ToggleMainMenu();
	
	//暴露给外边的变量以及组件
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetbLockOn();
	UFUNCTION(BlueprintCallable)
	void SetLockOn(bool Out_bLockOn);
	UFUNCTION(BlueprintCallable)
	void SetLeftAttackCount(int32 Count);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetLeftAttackCount();
	UFUNCTION(BlueprintCallable)
	void SetStartCombo(bool Out_StartCombo);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetStartCombo();
	UFUNCTION(BlueprintCallable)
	void SetRightAttack(bool Out_RightAttack);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetRightAttack();
	UFUNCTION(BlueprintCallable)
	void SetSprite(bool Out_bSprite);
	

	//功能类函数
	//攻击动画
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SaveAttack();
	UFUNCTION(BlueprintCallable)
	void ResetAttack();

	//功能测试
	void ForTesting();
	
protected:
	//写变量以及组件
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTargetComponent* TargetComponent;
	UPROPERTY(BlueprintReadWrite)
	bool bLockOn;//锁定状态
	

	//攻击动画
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bLeftAttack;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bSaveLeftAttack;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int32 LeftAttackCount;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bStartCombo;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bRightAttack;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bSprite;
	
	

protected:
	//写一些不被控制的函数
	UFUNCTION()
	void DoLockOn();
	UFUNCTION(BlueprintImplementableEvent)
	void PrintAttribute();
public:
	friend class UPlayerAnimInstance;
};
