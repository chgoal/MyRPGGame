// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkinInterface.generated.h"

class USkinComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USkinInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYRPGGAME_API ISkinInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual USkinComponent* GetSkinComponent() = 0;
	virtual USkeletalMeshComponent* GetSkinSkeletalMeshComponent() = 0;
	virtual void AddActorToCapture(AActor* Actor);
	virtual void RemoveActorToCapture(AActor* Actor);
	
};
