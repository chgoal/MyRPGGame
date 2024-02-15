// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Subsystem/WeaponSubsystem.h"
#include "BaseAnimInstance.generated.h"

class ABaseCharacter;
class UCurveVector;
/**
 * 
 */
UENUM()
enum class EMovementDirection:uint8
{
	EM_Forward,
	EM_Right,
	EM_Left,
	EM_Backward
};

UENUM(BlueprintType)
enum class EHitDirection:uint8
{
	EHD_Forward,
	EHD_Right,
	EHD_Left,
	EHD_Backward
};

USTRUCT(BlueprintType)
struct FVelocityBlend
{
	GENERATED_BODY()
public:
	FVelocityBlend()
	{
		F = 0.f;
		B = 0.f;
		L = 0.f;
		R = 0.f;
	}
	UPROPERTY(BlueprintReadOnly)
	float F;
	UPROPERTY(BlueprintReadOnly)
	float B;
	UPROPERTY(BlueprintReadOnly)
	float L;
	UPROPERTY(BlueprintReadOnly)
	float R;
};
UCLASS()
class MYRPGGAME_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UPROPERTY(BlueprintReadOnly)
	ABaseCharacter* BaseCharacter;

	//参数
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float Speed;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool bFalling;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float HitYaw;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	EWeaponState WeaponState;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	EHitDirection HitDirection;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool bHurt;
public:
	EHitDirection CalHitDirection(float Yaw);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	EHitDirection GetHitDirection();
};
