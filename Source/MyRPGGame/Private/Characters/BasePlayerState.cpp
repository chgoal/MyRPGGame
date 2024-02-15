// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BasePlayerState.h"

ABasePlayerState::ABasePlayerState()
{
	Health = 100.f;
	Mana = 100.f;
	Attack = 10.f;
	Defence = 5.f;
	
}

void ABasePlayerState::AddHealthGain(float Out_Health)
{
	HealthGain = HealthGain+ Out_Health;
}

void ABasePlayerState::SetHealthGain(float Out_Health)
{
	HealthGain = Out_Health;
}

void ABasePlayerState::AddManaGain(float Out_Mana)
{
	ManaGain = ManaGain+Out_Mana;
}

void ABasePlayerState::SetManaGain(float Out_Mana)
{
	ManaGain = Out_Mana;
}

void ABasePlayerState::AddAttackGain(float Out_Attack)
{
	AttackGain = AttackGain + Out_Attack;
}

void ABasePlayerState::SetAttackGain(float Out_Attack)
{
	AttackGain = Out_Attack;
}


