// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYRPGGAME_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	//基础数值
	UPROPERTY(EditAnywhere)
	float Health;
	UPROPERTY(EditAnywhere)
	float Mana;
	UPROPERTY(EditAnywhere)
	float Attack;
	UPROPERTY(EditAnywhere)
	float Defence;
	UPROPERTY(EditAnywhere)
	float JumpHeight;
	UPROPERTY(EditAnywhere)
	float MoveSpeed;
	UPROPERTY(EditAnywhere)
	bool IsLife;
	//增加数值
	float HealthGain;
	float ManaGain;
	float AttackGain;
	float DefenceGain;
	float JumpGain;
	float MoveSpeedGain;
public:
	ABasePlayerState();
	void AddHealthGain(float Out_Health);
	void SetHealthGain(float Out_Health);
	void AddManaGain(float Out_Mana);
	void SetManaGain(float Out_Mana);
	void AddAttackGain(float Out_Attack);
	void SetAttackGain(float Out_Attack);
	void AddDefenceGain(float Out_Defence);
	void SetDefenceGain(float Out_Defence);
	void AddJumpHeightGain(float Out_JumpHeight);
	void SetJumpHeightGain(float Out_JumpHeight);
	void AddMoveSpeedGain(float Out_MoveSpeed);
	void SetMoveSpeedGain(float Out_MoveSpeed);
	
	
	
};

inline void ABasePlayerState::SetMoveSpeedGain(float Out_MoveSpeed)
{
	MoveSpeedGain = Out_MoveSpeed;
}

inline void ABasePlayerState::AddMoveSpeedGain(float Out_MoveSpeed)
{
	MoveSpeedGain = MoveSpeedGain+Out_MoveSpeed;
}

inline void ABasePlayerState::SetJumpHeightGain(float Out_JumpHeight)
{
	JumpGain = Out_JumpHeight;
}

inline void ABasePlayerState::AddJumpHeightGain(float Out_JumpHeight)
{
	JumpGain = JumpGain+Out_JumpHeight;
}

inline void ABasePlayerState::SetDefenceGain(float Out_Defence)
{
	DefenceGain = Out_Defence;
}

inline void ABasePlayerState::AddDefenceGain(float Out_Defence)
{
	DefenceGain = DefenceGain + Out_Defence;
}
