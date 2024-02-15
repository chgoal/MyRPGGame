// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SkinInterface.h"
#include "PlayerModel.generated.h"

class APlayerCharacter;
class USkinComponent;
UCLASS()
class MYRPGGAME_API APlayerModel : public AActor,public ISkinInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerModel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// UFUNCTION(BlueprintImplementableEvent)
	// void AddToCapture(AActor* Actor);
	// UFUNCTION(BlueprintImplementableEvent)
	// void RemoveFromCapture(AActor* Actor);
	virtual USkinComponent* GetSkinComponent() override;
	virtual USkeletalMeshComponent* GetSkinSkeletalMeshComponent() override;

	void SetSkeletalMesh(USkeletalMesh* SkeletalMesh) const;
	void SetSkeletalMesh(TArray<USceneComponent*> SceneComponents);
	USkeletalMeshComponent* GetSkeletalMeshComponent();
	UStaticMeshComponent* GetStaticMeshComponent();
	

	UFUNCTION(BlueprintCallable)
	//用于添加捕捉
	virtual void AddActorToCapture(AActor* Actor) override;
	UFUNCTION(BlueprintCallable)
	//用于取消捕捉
	virtual void RemoveActorToCapture(AActor* Actor) override;
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCapture();
	UFUNCTION(BlueprintCallable)
	void SetPlayer(APlayerCharacter* Out_Player);
	APlayerCharacter* GetPlayer();
	
protected:
	//组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USkinComponent* SkinComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY()
	APlayerCharacter* Player;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> CaptureArray;

	/**
	 * @brief 增加的组件放在这里管理
	 */
	TArray<USkeletalMeshComponent*> AddedSkeletalMesh;
	TArray<UStaticMeshComponent*> AddedStaticMesh;

};



