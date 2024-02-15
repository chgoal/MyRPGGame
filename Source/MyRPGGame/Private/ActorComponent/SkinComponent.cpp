// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/SkinComponent.h"

#include "Actors/Weapon.h"
#include "Interface/SkinInterface.h"
#include "Subsystem/WeaponSubsystem.h"

// Sets default values for this component's properties
USkinComponent::USkinComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkinComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkinComponent::PutinSkin(ESkinType SkinType, int32 ID)
{
	if (SkinType == ESkinType::EST_NONE)
	{
		return;
	}
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetSkinByID(ID);
	if (!PropsBase)
	{
		return;
	}
	const FSkin* Skin = static_cast<const FSkin*>(PropsBase);
	if (Skin->SkeletalMeshes.Num() != 0 )
	{
		//如果是skeletalmesh的装备
		
		PutinSkinSkeletalMesh(SkinType,Skin);
		
	}
	else if (Skin->StaticMeshes.Num() != 0)
	{
		//如果是静态装备
		PutinSkinStaticMesh(SkinType,Skin);
	}
}

void USkinComponent::TakeOffSkin(ESkinType SkinType, int32 ID)
{
	ClearSkinSkeletalMesh(SkinType);
	ClearSkinStaticMesh(SkinType);
}

void USkinComponent::TakeOffAllSkin()
{
	UEnum* SkinEnum = StaticEnum<ESkinType>();
	for (int32 i = 0;i<SkinEnum->NumEnums()-1;i++)
	{
		ESkinType SkinType = ESkinType(SkinEnum->GetValueByIndex(i));
		ClearSkinSkeletalMesh(SkinType);
		ClearSkinStaticMesh(SkinType);
	}
}

void USkinComponent::PutinSkinSkeletalMesh(ESkinType SkinType, const FSkin* Skin)
{
	if (MultiSkeletalMeshMap.Contains(SkinType))
	{
		MultiSkeletalMeshMap[SkinType].bIsSkeletalMesh = true;//设置SkeletalMesh模式
		if (MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.Num()>=Skin->SkeletalMeshes.Num())//装备槽存在大于等于要装备的内容
		{
			for (auto i = 0;i < Skin->SkeletalMeshes.Num(); i++)
			{
				if (Skin->SkeletalMeshes[i])
				{
					MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->SetSkeletalMesh(Skin->SkeletalMeshes[i]);
					if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
					{
						MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,Skin->Socket);
						MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->SetMasterPoseComponent(SkinInterface->GetSkinSkeletalMeshComponent());
					}
				}
			}
		}
		else//装备槽存在，且装备槽小于要装备的内容
		{
			for (auto i = 0;i<Skin->SkeletalMeshes.Num() - MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.Num();i++)
			{
				USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(GetOwner());
				SkeletalMeshComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
				if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
				{
					SkeletalMeshComponent->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				}
				SkeletalMeshComponent->SetReceivesDecals(false);
				MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.Add(SkeletalMeshComponent);
			}
			PutinSkinSkeletalMesh(SkinType,Skin);
		}
	}
	else//装备槽不存在，添加装备槽
	{
		FSkeletalMeshArray Meshes;
		for (auto i = 0;i < Skin->SkeletalMeshes.Num(); i++)
		{
			USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(GetOwner());
			SkeletalMeshComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
			if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
			{
				SkeletalMeshComponent->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
			SkeletalMeshComponent->SetReceivesDecals(false);
			Meshes.SkeletalMeshComponents.Add(SkeletalMeshComponent);
		}
		
		MultiSkeletalMeshMap.Add(SkinType,Meshes);
		PutinSkinSkeletalMesh(SkinType,Skin);
		
	}
}

void USkinComponent::ClearSkinSkeletalMesh(ESkinType SkinType)
{
	if (!MultiSkeletalMeshMap.Contains(SkinType))
	{
		return;
	}
	for (auto i = 0;i < MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.Num();i++)
	{
		MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->SetMasterPoseComponent(nullptr,false);
		MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->SetSkeletalMesh(nullptr);
	}
}

void USkinComponent::PutinSkinStaticMesh(ESkinType SkinType, const FSkin* Skin)
{
	if (MultiSkeletalMeshMap.Contains(SkinType))
	{
		MultiSkeletalMeshMap[SkinType].bIsSkeletalMesh = false;//设置SkeletalMesh模式
		if (MultiSkeletalMeshMap[SkinType].StaticMeshComponents.Num()>=Skin->StaticMeshes.Num())//装备槽存在大于等于要装备的内容
		{
			for (auto i = 0;i < Skin->StaticMeshes.Num(); i++)
			{
				if (Skin->StaticMeshes[i])
				{
					MultiSkeletalMeshMap[SkinType].StaticMeshComponents[i]->SetStaticMesh(Skin->StaticMeshes[i]);
					if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
					{
						MultiSkeletalMeshMap[SkinType].StaticMeshComponents[i]->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,Skin->Socket);
					}
				}
			}
		}
		else//装备槽存在，且装备槽小于要装备的内容
		{
			for (auto i = 0;i<Skin->StaticMeshes.Num() - MultiSkeletalMeshMap[SkinType].StaticMeshComponents.Num();i++)
			{
				UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
				StaticMeshComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
				if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
				{
					StaticMeshComponent->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				}
				MultiSkeletalMeshMap[SkinType].StaticMeshComponents.Add(StaticMeshComponent);
			}
			PutinSkinStaticMesh(SkinType,Skin);
		}
	}
	else//装备槽不存在，添加装备槽
	{
		FSkeletalMeshArray Meshes;
		for (auto i = 0;i < Skin->StaticMeshes.Num(); i++)
		{
			UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
			StaticMeshComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
			if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
			{
				StaticMeshComponent->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
			Meshes.StaticMeshComponents.Add(StaticMeshComponent);
		}
		
		MultiSkeletalMeshMap.Add(SkinType,Meshes);
		PutinSkinStaticMesh(SkinType,Skin);
		
	}
}

void USkinComponent::ClearSkinStaticMesh(ESkinType SkinType)
{
	if (!MultiSkeletalMeshMap.Contains(SkinType))
	{
		return;
	}
	for (auto i = 0;i < MultiSkeletalMeshMap[SkinType].StaticMeshComponents.Num();i++)
	{
		MultiSkeletalMeshMap[SkinType].StaticMeshComponents[i]->SetStaticMesh(nullptr);
	}
}

void USkinComponent::DeleteSkinMesh(ESkinType SkinType)
{
	 if (MultiSkeletalMeshMap.Contains(SkinType))
	 {
	 	if (MultiSkeletalMeshMap[SkinType].StaticMeshComponents.Num()>0)
	 	{
	 		for (auto i=0;i<MultiSkeletalMeshMap[SkinType].StaticMeshComponents.Num();i++)
	 		{
	 			MultiSkeletalMeshMap[SkinType].StaticMeshComponents[i]->SetStaticMesh(nullptr);
	 			MultiSkeletalMeshMap[SkinType].StaticMeshComponents[i]->UnregisterComponent();
	 			MultiSkeletalMeshMap[SkinType].StaticMeshComponents[i]->DestroyComponent();
	 			MultiSkeletalMeshMap[SkinType].StaticMeshComponents.RemoveAt(i);
	 		}
	 	}
	 	
	 	if (MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.Num()>0)
	 	{
	 		for (auto i = 0;i < MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.Num();i++)
	 		{
	 			MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->SetMasterPoseComponent(nullptr,false);
	 			MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->SetSkeletalMesh(nullptr);
	 			MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->UnregisterComponent();
	 			MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents[i]->DestroyComponent();
	 			MultiSkeletalMeshMap[SkinType].SkeletalMeshComponents.RemoveAt(i);
	 		}
	 	}
	 	MultiSkeletalMeshMap.Remove(SkinType);//取消槽位
	 }
}

void USkinComponent::EquipWeapon(FWeaponMsg WeaponMsg)
{
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetWeaponsByID(WeaponMsg.ID);
	if (!PropsBase || PropsBase->ItemType != EItemType::EPT_Weapon)
	{
		return;
	}
	const FWeapons* Weapons = static_cast<const FWeapons*>(PropsBase);
	if (Weapons->MainWeaponActor.Get())
	{
		MainWeapon = GetOwner()->GetWorld()->SpawnActor<AWeapon>(Weapons->MainWeaponActor);
		if (MainWeapon)
		{
			MainWeapon->SetID(WeaponMsg.ID);
			MainWeapon->SetWeaponMsg(WeaponMsg);
			MainWeapon->SetbIsMain(true);//主手武器存储信息并且设置为主手武器
			if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
			{
				MainWeapon->WeaponSetMaster(SkinInterface,Weapons->MainSocketName);
				SkinInterface->AddActorToCapture(MainWeapon);
			}
		}
	}
	if (Weapons->OffWeaponActor.Get())
	{
		OffWeapon = GetOwner()->GetWorld()->SpawnActor<AWeapon>(Weapons->OffWeaponActor);
		if (OffWeapon)
		{
			OffWeapon->SetID(WeaponMsg.ID);
			if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
			{
				OffWeapon->WeaponSetMaster(SkinInterface,Weapons->OffSocketName);
				SkinInterface->AddActorToCapture(OffWeapon);
			}
		}
	}
	// if (MainWeapon && OffWeapon && WeaponMsg.bEquip)//用于枪类装备武器时使用
	// {
	// 	
	// }
	
}

void USkinComponent::UnEquipWeapon(FWeaponMsg WeaponMsg)
{
	
	FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,false);
	if (MainWeapon)
	{
		if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
		{
			SkinInterface->RemoveActorToCapture(MainWeapon);
		}
		MainWeapon->DetachFromActor(Rules);
		MainWeapon->Destroy();
		MainWeapon = nullptr;
	}
	if (OffWeapon)
	{
		if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
		{
			SkinInterface->RemoveActorToCapture(OffWeapon);
		}
		OffWeapon->DetachFromActor(Rules);
		OffWeapon->Destroy();
		OffWeapon = nullptr;
	}
}

void USkinComponent::EquipWeapon(TSubclassOf<AWeapon> Weapon,FName WeaponSocket,bool bMain)
{
	if (!Weapon)
	{
		return;
	}
	if (Weapon->GetClass())
	{
		if (bMain)
		{
			MainWeapon = GetOwner()->GetWorld()->SpawnActor<AWeapon>(Weapon);
            MainWeapon->SetbIsMain(true);
            if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
            {
            	MainWeapon->WeaponSetMaster(SkinInterface,WeaponSocket);
            }
		}
		else
		{
			OffWeapon = GetOwner()->GetWorld()->SpawnActor<AWeapon>(Weapon);
			OffWeapon->SetbIsMain(false);
			if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
			{
				OffWeapon->WeaponSetMaster(SkinInterface,WeaponSocket);
			}
		}
		
	}
}

void USkinComponent::UnEquipWeapon(bool bMain)
{
	if (bMain)
	{
		if (MainWeapon)
		{
			MainWeapon->Destroy();
		}
		
	}
	else
	{
		if (OffWeapon)
		{
			OffWeapon->Destroy();
		}
	}
}

void USkinComponent::UnEquipWeapon()
{
	FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,false);
	if (MainWeapon)
	{
		if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
		{
			SkinInterface->RemoveActorToCapture(MainWeapon);
		}
		MainWeapon->DetachFromActor(Rules);
		MainWeapon->Destroy();
		MainWeapon = nullptr;
	}
	if (OffWeapon)
	{
		if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
		{
			SkinInterface->RemoveActorToCapture(OffWeapon);
		}
		OffWeapon->DetachFromActor(Rules);
		OffWeapon->Destroy();
		OffWeapon = nullptr;
	}
}

void USkinComponent::LaunchWeapon(bool bIsMainWeapon)
{
	if (bIsMainWeapon)
	{
		MainWeapon->TryToAttack();
	}
	else
	{
		OffWeapon->TryToAttack();
	}
}

void USkinComponent::SettlementWeapon(float Damage,bool bIsMainWeapon)
{
	if (bIsMainWeapon)
	{
		MainWeapon->TrySettlementAttack(Damage);
	}
	else
	{
		OffWeapon->TrySettlementAttack(Damage);
	}
}

void USkinComponent::StopWeapon(bool bIsMainWeapon)
{
	if (bIsMainWeapon)
	{
		MainWeapon->StopAttack();
	}
	else
	{
		OffWeapon->StopAttack();
	}
}

AWeapon* USkinComponent::GetWeapon(bool bIsMain)
{
	if (bIsMain)
	{
		return MainWeapon;
	}
	else
	{
		return OffWeapon;
	}
}


