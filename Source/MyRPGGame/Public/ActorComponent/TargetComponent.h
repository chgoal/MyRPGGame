// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


class AEnemyCharacter;
class ABaseCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPGGAME_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	bool bUseControllerRotationYaw;
	bool bOrientRotationToMovement;
	bool bUseControllerDesiredRotation;
	UPROPERTY()
	ABaseCharacter* FocusActor;
	UPROPERTY(EditDefaultsOnly,Category="Trace")
	float TargetOffset;
	UPROPERTY(EditDefaultsOnly,Category="Trace")
	float TraceDistance;
	UPROPERTY(EditDefaultsOnly,Category="Trace")
	float TraceRadius;
	UPROPERTY(EditDefaultsOnly,Category="Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;
	UPROPERTY(EditDefaultsOnly,Category="MoveMent")
	float LockMoveSpeed;
	UPROPERTY(EditDefaultsOnly,Category="MoveMent")
	float UnLockMoveSpeed;
	UPROPERTY(EditAnywhere,Category="TickKey")
	bool TickKey;
	
public:
	void ChangeRotationMode();
	void RestoreRotationMode();
	void Target(AEnemyCharacter* TargetActor);
	UFUNCTION(BlueprintCallable)
	void CancelTarget();
	UFUNCTION(BlueprintCallable)
	void FindTarget();
	UFUNCTION(BlueprintCallable)
	void SetTickKey(bool Out_TickKey);

		
};
