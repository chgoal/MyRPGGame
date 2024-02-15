// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPGGAME_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
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
inline void UAttributeComponent::SetMoveSpeedGain(float Out_MoveSpeed)
{
	MoveSpeedGain = Out_MoveSpeed;
}

inline void UAttributeComponent::AddMoveSpeedGain(float Out_MoveSpeed)
{
	MoveSpeedGain = MoveSpeedGain+Out_MoveSpeed;
}

inline void UAttributeComponent::SetJumpHeightGain(float Out_JumpHeight)
{
	JumpGain = Out_JumpHeight;
}

inline void UAttributeComponent::AddJumpHeightGain(float Out_JumpHeight)
{
	JumpGain = JumpGain+Out_JumpHeight;
}

inline void UAttributeComponent::SetDefenceGain(float Out_Defence)
{
	DefenceGain = Out_Defence;
}

inline void UAttributeComponent::AddDefenceGain(float Out_Defence)
{
	DefenceGain = DefenceGain + Out_Defence;
}
inline void UAttributeComponent::AddHealthGain(float Out_Health)
{
	HealthGain = HealthGain+ Out_Health;
}

inline void UAttributeComponent::SetHealthGain(float Out_Health)
{
	HealthGain = Out_Health;
}

inline void UAttributeComponent::AddManaGain(float Out_Mana)
{
	ManaGain = ManaGain+Out_Mana;
}

inline void UAttributeComponent::SetManaGain(float Out_Mana)
{
	ManaGain = Out_Mana;
}

inline void UAttributeComponent::AddAttackGain(float Out_Attack)
{
	AttackGain = AttackGain + Out_Attack;
}

inline void UAttributeComponent::SetAttackGain(float Out_Attack)
{
	AttackGain = Out_Attack;
}