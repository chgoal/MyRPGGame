// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/EnemyAnimInstance.h"

#include "Characters/EnemyCharacter.h"
#include "Curves/CurveVector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!Enemy)
	{
		Enemy = Cast<AEnemyCharacter>(TryGetPawnOwner());
		return;
	}
	bLock = Enemy->bLock;
	HorizDirect = CalculateDirection(Enemy->GetVelocity(),Enemy->GetControlRotation());
	Rest = Enemy->bRest;
	RandomNum = Enemy->RandomNum;
	Sit = Enemy->bSit;
	bLoseEnemy = Enemy->bLoseEnemy;
	bEquip = Enemy->bEquip;
}

EMovementDirection UEnemyAnimInstance::CalMovementDirection()
{
	FRotator T_Rotator;
	T_Rotator = Enemy->GetCharacterMovement()->Velocity.ToOrientationRotator()-Enemy->GetBaseAimRotation();
	return CalculateQuadrant(MovementDirection,T_Rotator.Yaw);
}

EMovementDirection UEnemyAnimInstance::CalculateQuadrant(EMovementDirection CurrentState,float Angle,float FR_Threshold,float FL_Threshold,float BR_Threshold,float BL_Threshold,float Buffer)
{
	if (AngleInRange(Angle,FL_Threshold,FR_Threshold,Buffer,CurrentState!=EMovementDirection::EM_Forward||CurrentState!=EMovementDirection::EM_Backward))
	{
		return EMovementDirection::EM_Forward;
	}
	if (AngleInRange(Angle,FR_Threshold,BR_Threshold,Buffer,CurrentState!=EMovementDirection::EM_Right||CurrentState!=EMovementDirection::EM_Left))
	{
		return EMovementDirection::EM_Right;
	}
	if (AngleInRange(Angle,BL_Threshold,FL_Threshold,Buffer,CurrentState!=EMovementDirection::EM_Right || CurrentState!=EMovementDirection::EM_Left))
	{
		return EMovementDirection::EM_Left;
	}
	return EMovementDirection::EM_Backward;
}

bool UEnemyAnimInstance::AngleInRange(float Angle, float Min_Angle, float Max_Angle, float Buffer, bool IncreaseBuffer)
{
	if (IncreaseBuffer)
	{
		return UKismetMathLibrary::InRange_FloatFloat(Angle,Min_Angle-Buffer,Max_Angle+Buffer);
	}
	else
	{
		return UKismetMathLibrary::InRange_FloatFloat(Angle,Min_Angle+Buffer,Max_Angle-Buffer);
	}
}

void UEnemyAnimInstance::UpdateRotationValues()
{
	MovementDirection = CalMovementDirection();
	if (YawOffsetFB)
	{
		
		FVector OffsetFB =  YawOffsetFB->GetVectorValue((Velocitys.ToOrientationRotator()-BaseCharacter->GetControlRotation()).Yaw);
		FYaw = OffsetFB.X;
		BYaw = OffsetFB.Y;
		
	}
	if (YawOffsetLR)
	{
		FVector OffsetLR =  YawOffsetLR->GetVectorValue((Velocitys.ToOrientationRotator()-BaseCharacter->GetControlRotation()).Yaw);
		FYaw = OffsetLR.X;
		BYaw = OffsetLR.Y;
	}
}

void UEnemyAnimInstance::UpdateMovementValues()
{
	VelocityBlends = InterpVelocityBlend(VelocityBlends,CalculateVelocityBlend(),12.f,UpdateDeltaTime);
}

FVelocityBlend UEnemyAnimInstance::CalculateVelocityBlend()
{
	FVector Velocity = BaseCharacter->GetVelocity();
	FVector LocRelativeVelocityDir;
	FVector RelativeDirection;
	float Sum;
	FVelocityBlend VelocityBlend;
	UKismetMathLibrary::Vector_Normalize(Velocity,0.1);
	LocRelativeVelocityDir = UKismetMathLibrary::LessLess_VectorRotator(Velocity,BaseCharacter->GetActorRotation());
	Sum = UKismetMathLibrary::Abs(LocRelativeVelocityDir.X)+UKismetMathLibrary::Abs(LocRelativeVelocityDir.Y)+UKismetMathLibrary::Abs(LocRelativeVelocityDir.Z);
	RelativeDirection = LocRelativeVelocityDir/Sum;
	VelocityBlend.F = UKismetMathLibrary::FClamp(RelativeDirection.X,0.f,1.f);
	VelocityBlend.B = UKismetMathLibrary::Abs(UKismetMathLibrary::FClamp(RelativeDirection.X,-1.f,0.f));
	VelocityBlend.L = UKismetMathLibrary::Abs(UKismetMathLibrary::FClamp(RelativeDirection.Y,-1.f,0.f));
	VelocityBlend.R = UKismetMathLibrary::FClamp(RelativeDirection.Y,0.f,1.f);
	return VelocityBlend;
}

FVelocityBlend UEnemyAnimInstance::InterpVelocityBlend(FVelocityBlend Current, FVelocityBlend Target, float InterpSpeed,
	float DeltaTime)
{
	FVelocityBlend VelocityBlend;
	VelocityBlend.F = UKismetMathLibrary::FInterpTo(Current.F,Target.F,DeltaTime,InterpSpeed);
	VelocityBlend.B = UKismetMathLibrary::FInterpTo(Current.B,Target.B,DeltaTime,InterpSpeed);
	VelocityBlend.L = UKismetMathLibrary::FInterpTo(Current.L,Target.L,DeltaTime,InterpSpeed);
	VelocityBlend.R = UKismetMathLibrary::FInterpTo(Current.R,Target.R,DeltaTime,InterpSpeed);
	return VelocityBlend;
}


