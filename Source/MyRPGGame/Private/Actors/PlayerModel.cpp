// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerModel.h"

#include "ActorComponent/PackageComponent.h"
#include "ActorComponent/SkinComponent.h"
#include "Characters/PlayerCharacter.h"

// Sets default values
APlayerModel::APlayerModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SkinComponent = CreateDefaultSubobject<USkinComponent>(TEXT("SkinComp"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USkinComponent* APlayerModel::GetSkinComponent()
{
	return SkinComponent;
}

USkeletalMeshComponent* APlayerModel::GetSkinSkeletalMeshComponent()
{
	return SkeletalMeshComponent;
}

void APlayerModel::SetSkeletalMesh(USkeletalMesh* SkeletalMesh) const
{
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
}

void APlayerModel::SetSkeletalMesh(TArray<USceneComponent*> SceneComponents)
{
	for (auto SComp:SceneComponents)
	{
		if (USkeletalMeshComponent* SkeletalMeshComp = Cast<USkeletalMeshComponent>(SComp))
		{
			if (SkeletalMeshComp->SkeletalMesh)
			{
				GetSkeletalMeshComponent()->SetSkeletalMesh(SkeletalMeshComp->SkeletalMesh);
			}
		}
		if (UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(SComp))
		{
			if (StaticMeshComp->GetStaticMesh())
			{
				GetStaticMeshComponent()->SetStaticMesh(StaticMeshComp->GetStaticMesh());
			}
		}
	}
}

USkeletalMeshComponent* APlayerModel::GetSkeletalMeshComponent()
{
	USkeletalMeshComponent* SkeletalComp = NewObject<USkeletalMeshComponent>(this);
    SkeletalComp->RegisterComponentWithWorld(GetWorld());
    SkeletalComp->AttachToComponent(SkeletalMeshComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SkeletalComp->SetMasterPoseComponent(SkeletalMeshComponent);
	AddedSkeletalMesh.Add(SkeletalComp);
    return SkeletalComp;
}

UStaticMeshComponent* APlayerModel::GetStaticMeshComponent()
{
	UStaticMeshComponent* StaticComp = NewObject<UStaticMeshComponent>(this);
	StaticComp->RegisterComponentWithWorld(GetWorld());
	StaticComp->AttachToComponent(SkeletalMeshComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AddedStaticMesh.Add(StaticComp);
	return StaticComp;
}

void APlayerModel::AddActorToCapture(AActor* Actor)
{
	if (CaptureArray.Contains(Actor))
	{
		return;
	}
	CaptureArray.Add(Actor);
	UpdateCapture();
}

void APlayerModel::RemoveActorToCapture(AActor* Actor)
{
	if (CaptureArray.Contains(Actor))
	{
		CaptureArray.Remove(Actor);
	}
	UpdateCapture();
}

void APlayerModel::SetPlayer(APlayerCharacter* Out_Player)
{
	Player = Out_Player;
}

APlayerCharacter* APlayerModel::GetPlayer()
{
	return Player;
}



