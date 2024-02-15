// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyRPGGame/Public/Anim/BaseAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UPlayerAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	APlayerCharacter* Player;
	//参数
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	FVector Velocitys;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool bLockOn;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float MoveDirection;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float SpriteDirection;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float UpdateDeltaTime;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool RightAttack;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool bSprite;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool bRoll;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool Running;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	float MoveX;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	float MoveY;

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
public:
	UFUNCTION(BlueprintCallable)
    	EMovementDirection CalDirection();
    	UFUNCTION(BlueprintCallable)
    	EMovementDirection CalculateQuadrant(EMovementDirection CurrentState,float Angle,float FR_Threshold = 70.f,float FL_Threshold = -70.f,float BR_Threshold = 110.f,float BL_Threshold = -110.f,float Buffer = 5.f);
    	UFUNCTION(BlueprintCallable)
    	bool AngleInRange(float Angle,float Min_Angle,float Max_Angle,float Buffer,bool IncreaseBuffer);
    	void UpdateRotationValues();
    	void UpdateMovementValues();
    	FVelocityBlend CalculateVelocityBlend();
    	FVelocityBlend InterpVelocityBlend(FVelocityBlend Current,FVelocityBlend Target,float InterpSpeed,float DeltaTime);
};
