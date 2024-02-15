// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SceneActor.h"

#include "MyRPGGame/MyRPGGame.h"

// Sets default values
ASceneActor::ASceneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionObjectType(ECC_SceneActor);

}

// Called when the game starts or when spawned
void ASceneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

