// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISense_Sight.h"
#include "BaseAISense_Sight.generated.h"

class ASceneActor;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UBaseAISense_Sight : public UAISense_Sight
{
	GENERATED_BODY()
public:
	virtual void RegisterSource(AActor& SourceActors) override;
protected:
	UPROPERTY(EditAnywhere)
	ASceneActor* SceneActor;
};
