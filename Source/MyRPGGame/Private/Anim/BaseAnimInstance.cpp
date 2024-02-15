// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRPGGame/Public/Anim/BaseAnimInstance.h"


#include "GameFramework/CharacterMovementComponent.h"
#include "MyRPGGame/Public/Characters/BaseCharacter.h"

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!BaseCharacter)
	{
		BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
		return;
	}
	
	Speed = BaseCharacter->GetVelocity().Size();
	bFalling = BaseCharacter->GetCharacterMovement()->IsFalling();
	WeaponState = BaseCharacter->GetWeaponState();
	//HitDirection = CalHitDirection(BaseCharacter->HitYaw);
	bHurt = BaseCharacter->bHurt;
}

EHitDirection UBaseAnimInstance::CalHitDirection(float Yaw)
{
	Yaw = HitYaw = BaseCharacter->HitYaw;
	if (Yaw<=45 && Yaw>=-45)
	{
		return EHitDirection::EHD_Forward;
	}
	 if (Yaw>=45 && Yaw<=150)
	{
		return EHitDirection::EHD_Right;
	}
	 if (Yaw<=-45 && Yaw>=-150)
	{
		return EHitDirection::EHD_Left;
	}
		return EHitDirection::EHD_Backward;
}

EHitDirection UBaseAnimInstance::GetHitDirection()
{
	return HitDirection;
}






