// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/BaseAnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UEnemyAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UFUNCTION(BlueprintCallable)
	EMovementDirection CalMovementDirection();
	UFUNCTION(BlueprintCallable)
	EMovementDirection CalculateQuadrant(EMovementDirection CurrentState,float Angle,float FR_Threshold = 70.f,float FL_Threshold = -70.f,float BR_Threshold = 110.f,float BL_Threshold = -110.f,float Buffer = 5.f);
	UFUNCTION(BlueprintCallable)
	bool AngleInRange(float Angle,float Min_Angle,float Max_Angle,float Buffer,bool IncreaseBuffer);
	void UpdateRotationValues();
	void UpdateMovementValues();
	FVelocityBlend CalculateVelocityBlend();
	FVelocityBlend InterpVelocityBlend(FVelocityBlend Current,FVelocityBlend Target,float InterpSpeed,float DeltaTime);
protected:
	UPROPERTY()
	AEnemyCharacter* Enemy;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool bLock;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool Rest;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	int32 RandomNum;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	float HorizDirect;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool Sit;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool bLoseEnemy;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool bEquip;
	
	

	//参数
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	FVector Velocitys;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float UpdateDeltaTime;
	//素材
	UPROPERTY(EditAnywhere)
	UCurveVector* YawOffsetFB;
	UPROPERTY(EditAnywhere)
	UCurveVector* YawOffsetLR;
	
	//偏移
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float FYaw;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float BYaw;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float LYaw;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float RYaw;
    
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	EMovementDirection MovementDirection;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	FVelocityBlend VelocityBlends;
	
};
