// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AimUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class MYRPGGAME_API UAimUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentSizeBox;
public:
	UPROPERTY(EditAnywhere,Category="UI")
	FVector WorldOffset;
	UPROPERTY(BlueprintReadOnly,Category="UI")
	AActor* AttachedActor;
	
};
