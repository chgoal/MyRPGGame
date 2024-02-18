// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SceneItem.h"
#include "Components/BillboardComponent.h"
#include "Controller/RPGPlayerController.h"
#include "Data/DataAsset/WeaponDataAsset.h"
#include "GameInstance/CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyRPGGame/MyRPGGame.h"

// Sets default values
ASceneItem::ASceneItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillComp"));
	BillboardComponent->SetupAttachment(RootComponent);
	ItemType = EItemType::EPT_Tool;
	bThrow = false;
	

}

// Called when the game starts or when spawned
void ASceneItem::BeginPlay()
{
	Super::BeginPlay();
	InitMaxID();
	RandomIDAndNumber();
	InitActor();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ASceneItem::BgSpawn,0.6f);
	
	
}

void ASceneItem::BgSpawn()
{
	if (UWeaponSubsystem* WeaponSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		if (WeaponSubsystem->Check_IfDestroyed(ActorID))
		{
			Destroy();
		}
	}
	
}

// Called every frame
void ASceneItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASceneItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
}

EItemType ASceneItem::GetItemType()
{
	return ItemType;
}

int32 ASceneItem::GetNumber()
{
	return Number;
}

int32 ASceneItem::GetID()
{
	return ID;
}

FWeaponMsg ASceneItem::GetWeaponMsg()
{
	return WeaponMsg;
}

bool ASceneItem::GetbThrow()
{
	return bThrow;
}

void ASceneItem::SetID(int32 Out_ID)
{
	ID = Out_ID;
	WeaponMsg.ID = ID;
}

void ASceneItem::SetNumber(int32 Out_Number)
{
	Number = Out_Number;
}

void ASceneItem::SetPropsType(EItemType Out_ItemType)
{
	ItemType = Out_ItemType;
}

void ASceneItem::SetWeaponMsg(FWeaponMsg Out_WeaponMsg)
{
	WeaponMsg = Out_WeaponMsg;
}

void ASceneItem::SetbThrow(bool Out_bThrow)
{
	bThrow = Out_bThrow;
}

void ASceneItem::InitActor()
{
	if (ID > MaxID || ID < 0)
	{
		return;
	}
	if (ItemType == EItemType::EPT_Weapon)
	{
		const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetWeaponsByID(ID);
		if (PropsBase)
		{
			if (const FWeapons* Weapons = static_cast<const FWeapons*>(PropsBase))
			{
				if (Weapons->StaticMesh)
				{
					GetStaticComponent()->SetStaticMesh(Weapons->StaticMesh);
				}
				if (Weapons->SkeletalMesh)
				{
					GetSkeletalMeshComponent()->SetSkeletalMesh(Weapons->SkeletalMesh);
				}
				if (!bThrow)
				{
					WeaponMsg = Weapons->DataAsset.GetDefaultObject()->GetWeaponMsg();
					WeaponMsg.ID = ID;
				}
			}
		}
	}
	if (ItemType == EItemType::EPT_Tool)
	{
		const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetPropsByID(ID);
		if (PropsBase)
		{
			if (const FProps* Props = static_cast<const FProps*>(PropsBase))
			{
				if (Props->StaticMesh)
				{
					GetStaticComponent()->SetStaticMesh(Props->StaticMesh);
				}
				if (Props->SkeletalMesh)
				{
					GetSkeletalMeshComponent()->SetSkeletalMesh(Props->SkeletalMesh);
				}
			}
		}
	}
	if (ItemType == EItemType::EPT_Skin)
	{
		const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetSkinByID(ID);
		if (PropsBase)
		{
			if (const FSkin* Skin = static_cast<const FSkin*>(PropsBase))
			{
				if (Skin->StaticMeshes.Num() > 0)
				{
					if (Skin->StaticMeshes.Num() == 1)
					{
						GetStaticComponent()->SetStaticMesh(Skin->StaticMeshes[0]);
					}
					else
					{
						GetStaticComponent()->SetStaticMesh(Skin->StaticMeshes[0]);
						for (auto i = 1;i < Skin->StaticMeshes.Num();i++)
						{
							NewStaticMeshComponent()->SetStaticMesh(Skin->StaticMeshes[i]);
						}
					}
					
				}
				else if (Skin->SkeletalMeshes.Num() > 0)
				{
					if (Skin->SkeletalMeshes.Num() == 1)
					{
						GetSkeletalMeshComponent()->SetSkeletalMesh(Skin->SkeletalMeshes[0]);
					}
					else
					{
						GetSkeletalMeshComponent()->SetSkeletalMesh(Skin->SkeletalMeshes[0]);
						for (auto i = 1;i < Skin->SkeletalMeshes.Num();i++)
						{
							NewSkeletalMeshComponent()->SetSkeletalMesh(Skin->SkeletalMeshes[i]);
						}
					}
					
				}
			}
		}
	}
}

void ASceneItem::RandomIDAndNumber()
{
	if (!bRandom || MaxID<=0)
	{
		return;
	}
	
	if (bRandom)
	{
		if (bItemRandom)
		{
			RandomItem();
		}
		ID = FMath::RandRange(0,MaxID);
		if (ItemType == EItemType::EPT_Tool)
		{
			Number = FMath::RandRange(MinNumber,MaxNumber);
		}
	}
	
}

void ASceneItem::RandomItem()
{
	int32 Item;
	Item = FMath::RandRange(0,2);
	switch (Item)
	{
	case 0:
		{
			ItemType = EItemType::EPT_Skin;
			break;
		}
	case 1:
		{
			ItemType = EItemType::EPT_Weapon;
			break;
		}
	case 2:
		{
			ItemType = EItemType::EPT_Tool;
			break;
		}
		default:
		{
			ItemType = EItemType::EPT_Tool;
			break;
		}
	}
	
	
}

void ASceneItem::InitMaxID()
{
	switch (ItemType)
	{
	case EItemType::EPT_Skin:
		{
			MaxID = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetMaxSkin();
			break;
		}
	case EItemType::EPT_Tool:
		{
			MaxID = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetMaxProps();
			break;
		}
	case EItemType::EPT_Weapon:
		{
			MaxID = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetMaxWeapon();
			break;
		}
	}
}

void ASceneItem::PickUp()
{
	if (GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->DestroyItem(ActorID);
	}
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ASceneItem::K2_DestroyActor,0.2f);
}

UStaticMeshComponent* ASceneItem::GetStaticComponent()
{
	if (StaticMeshComponent)
	{
		return StaticMeshComponent;
	}
	StaticMeshComponent = NewObject<UStaticMeshComponent>(this);
	StaticMeshComponent->RegisterComponentWithWorld(GetWorld());
	StaticMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	StaticMeshComponent->SetCollisionObjectType(ECC_SceneItem);//这里是设置Channel碰撞
	return StaticMeshComponent;
}

USkeletalMeshComponent* ASceneItem::GetSkeletalMeshComponent()
{
	if (SkeletalMeshComponent)
	{
		return SkeletalMeshComponent;
	}
	SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this);
	SkeletalMeshComponent->RegisterComponentWithWorld(GetWorld());
	SkeletalMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SkeletalMeshComponent->SetGenerateOverlapEvents(true);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetCollisionObjectType(ECC_SceneItem);//添加新追踪方式
	return SkeletalMeshComponent;
	
}

UStaticMeshComponent* ASceneItem::NewStaticMeshComponent()
{
	UStaticMeshComponent* NewStaticComponent = NewObject<UStaticMeshComponent>(this);
	NewStaticComponent->RegisterComponentWithWorld(GetWorld());
	NewStaticComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	NewStaticComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponents.Add(NewStaticComponent);
	return NewStaticComponent;
}

USkeletalMeshComponent* ASceneItem::NewSkeletalMeshComponent()
{
	USkeletalMeshComponent* SkeletalComponent = NewObject<USkeletalMeshComponent>(this);
	SkeletalComponent->RegisterComponentWithWorld(GetWorld());
	SkeletalComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SkeletalComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponents.Add(SkeletalComponent);
	return SkeletalComponent;
}

