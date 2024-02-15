// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon.h"

#include "Actors/PlayerModel.h"
#include "Characters/BaseCharacter.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	bIsMain = false;
	bEquip = false;
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetReceiveDecals(false);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



EWeaponState AWeapon::GetWeaponState()
{
	return WeaponState;
}

int32 AWeapon::GetID()
{
	return ID;
}

FWeaponMsg AWeapon::GetWeaponMsg()
{
	return WeaponMsg;
}

bool AWeapon::GetbIsMain()
{
	return bIsMain;
}

bool AWeapon::GetbEquip()
{
	return bEquip;
}

void AWeapon::SetWeaponState(EWeaponState Out_WeaponState)
{
	WeaponState = Out_WeaponState;
}

void AWeapon::SetID(int32 Out_ID)
{
	ID = Out_ID;
}

void AWeapon::SetWeaponMsg(FWeaponMsg Out_WeaponMsg)
{
	WeaponMsg = Out_WeaponMsg;
	WeaponMsg.ID = ID;
}

void AWeapon::SetReceiveDecals(bool bNewReceivesDecals)
{
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetReceivesDecals(bNewReceivesDecals);
	}
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetReceivesDecals(bNewReceivesDecals);
	}
}

void AWeapon::WeaponSetMaster(ISkinInterface* SkinInterface,FName SocketName)
{
	if (SkinInterface)
	{
		MineSkinInterface = SkinInterface;
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(SkinInterface))
		{
			SetOwner(BaseCharacter);
			AttachToComponent(BaseCharacter->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,SocketName);
		}
		else if (APlayerModel* PlayerModel = Cast<APlayerModel>(SkinInterface))
		{
			SetOwner(PlayerModel);
			AttachToComponent(PlayerModel->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,SocketName);
		}
		
	}
}



void AWeapon::ClearMaster()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	SetOwner(nullptr);
	MineSkinInterface = nullptr;
}

void AWeapon::HideWeapon(bool bVisibility)
{
	//UE_LOG(LogTemp, Log, TEXT("HideWeapon"))
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetVisibility(bVisibility);
		//UE_LOG(LogTemp, Log, TEXT("StaticMeshComponent"))
	}
	if (SkeletalMeshComponent)
	{
		//UE_LOG(LogTemp, Log, TEXT("SkeletalMeshComponent"))
		SkeletalMeshComponent->SetVisibility(bVisibility);
	}
}

