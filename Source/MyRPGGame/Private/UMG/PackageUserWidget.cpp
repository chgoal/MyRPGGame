// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PackageUserWidget.h"

#include "ActorComponent/PackageComponent.h"
#include "ActorComponent/SkinComponent.h"
#include "Actors/PlayerModel.h"
#include "Blueprint/DragDropOperation.h"
#include "Characters/PlayerCharacter.h"
#include "Components/VerticalBox.h"
#include "UMG/BoundKeyUserWidget.h"
#include "UMG/ItemUserWidget.h"
#include "UMG/QuickUseUserWidget.h"
#include "UMG/ScollerBoxUserWidget.h"
#include "UMG/SkinSocketUserWidget.h"
#include "UMG/WeaponUserWidget.h"

void UPackageUserWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayer()->GetPawn()))
	{
		if (NearItemScoller && PackageItemScoller)
		{
			NearItemScoller->SetPackageWidget(this);
			PackageItemScoller->SetPackageWidget(this);
			PackageItemScoller->Reload();
			TArray<ASceneItem*> NearItem;
			Player->GetPackageComponent()->GetNearItem(NearItem);
            for (const auto Item :NearItem)
            {
            	NearItemScoller->AddItemUserWidget(Item);
            }
			
		}
		ReloadPropsWidget();
		ReloadSkinWidget();
		ReloadWeaponWidget();
		//绑定通知
		Player->GetPackageComponent()->OnNearItemEnter.AddUObject(this,&UPackageUserWidget::OnNearItemEnter);
		Player->GetPackageComponent()->OnNearItemLeave.AddUObject(this,&UPackageUserWidget::OnNearItemLeave);
		Player->GetPackageComponent()->OnPackageItemAdded.AddUObject(this,&UPackageUserWidget::OnAddItemToPackage);
		Player->GetPackageComponent()->OnPackageItemRemove.AddUObject(this,&UPackageUserWidget::OnRemoveItemFromPackage);
		Player->GetPackageComponent()->OnSkinPuton.AddUObject(this,&UPackageUserWidget::PutinSkin);
		Player->GetPackageComponent()->OnSkinTakeOff.AddUObject(this,&UPackageUserWidget::TakeOffSkin);
		Player->GetPackageComponent()->OnWeaponAdded.AddUObject(this,&UPackageUserWidget::AddWeaponToPackage);
		Player->GetPackageComponent()->OnWeaponRemoved.AddUObject(this,&UPackageUserWidget::RemoveWeaponFromPackage);
		Player->GetPackageComponent()->OnWeaponExChanged.AddUObject(this,&UPackageUserWidget::ExChangeWeapon);
		Player->GetPackageComponent()->OnPropsBoundAdded.AddUObject(this,&UPackageUserWidget::BoundProps);
		Player->GetPackageComponent()->OnPropsBoundRemove.AddUObject(this,&UPackageUserWidget::UnBoundProps);
		
		if (!PlayerModel)
		{
			TSubclassOf<APlayerModel> PlayerModelClass = LoadClass<APlayerModel>(nullptr,TEXT("Blueprint'/Game/Projecte/Blueprint/Actors/Model/BP_PlayerModel.BP_PlayerModel_C'"));
			PlayerModel = GetOwningPlayer()->GetWorld()->SpawnActor<APlayerModel>(PlayerModelClass,Player->GetActorLocation()+FVector(0,0,2000),FRotator::ZeroRotator);
			PlayerModel->SetPlayer(Player);
			PlayerModel->SetSkeletalMesh(Player->GetSkinSkeletalMeshComponent()->SkeletalMesh);
			PlayerModel->SetSkeletalMesh(Player->GetMainSkeletalMeshAttachChild());
		}
		PlayerModel->SetActorHiddenInGame(false);
		//隐藏武器
		Player->GetPackageComponent()->OnSkinPuton.AddUObject(PlayerModel->GetSkinComponent(),&USkinComponent::PutinSkin);
		Player->GetPackageComponent()->OnSkinTakeOff.AddUObject(PlayerModel->GetSkinComponent(),&USkinComponent::TakeOffSkin);
		Player->GetPackageComponent()->OnWeaponEquip.AddUObject(PlayerModel->GetSkinComponent(),&USkinComponent::EquipWeapon);
		Player->GetPackageComponent()->OnWeaponUnEquip.AddUObject(PlayerModel->GetSkinComponent(),&USkinComponent::UnEquipWeapon);
		//Player->GetPackageComponent()->OnWeaponExChanged.AddUObject(PlayerModel->GetSkinComponent(),)
		
	}
	
}

void UPackageUserWidget::RemoveFromParent()
{
	if (NearItemScoller)
	{
		NearItemScoller->ClearAll();
	}
	if (PackageItemScoller)
	{
		PackageItemScoller->ResetAll();
	}
	if (GetOwningPlayer())
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayer()->GetPawn()))
        {
        	Player->GetPackageComponent()->OnNearItemEnter.RemoveAll(this);
        	Player->GetPackageComponent()->OnNearItemLeave.RemoveAll(this);
			Player->GetPackageComponent()->OnPackageItemAdded.RemoveAll(this);
			Player->GetPackageComponent()->OnPackageItemRemove.RemoveAll(this);
			Player->GetPackageComponent()->OnSkinPuton.RemoveAll(this);
			Player->GetPackageComponent()->OnSkinTakeOff.RemoveAll(this);
			Player->GetPackageComponent()->OnWeaponAdded.RemoveAll(this);
			Player->GetPackageComponent()->OnWeaponRemoved.RemoveAll(this);
			Player->GetPackageComponent()->OnWeaponExChanged.RemoveAll(this);
			Player->GetPackageComponent()->OnPropsBoundAdded.RemoveAll(this);
			Player->GetPackageComponent()->OnPropsBoundRemove.RemoveAll(this);
        }
	}
	if (OnScreenWidgetClose.IsBound())
	{
		OnScreenWidgetClose.Broadcast();
	}
	Super::RemoveFromParent();
}

bool UPackageUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(InOperation->Payload))
	{
		if (!ItemUserWidget->GetSceneItem())
		{
			if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
			{
				if (Player->GetPackageComponent())
				{
					Player->GetPackageComponent()->RemoveItemFromPackage(ItemUserWidget->GetItemSite());
					return true;
				}
			}
		}
	}
	if (USkinSocketUserWidget* SocketUserWidget = Cast<USkinSocketUserWidget>(InOperation->Payload))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (Player->GetPackageComponent())
			{
				Player->GetPackageComponent()->TakeOffSkinToWorld(SocketUserWidget->GetSkinType(),true);
			}
		}
	}
	if (UWeaponUserWidget* WeaponUserWidget = Cast<UWeaponUserWidget>(InOperation->Payload))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (Player->GetPackageComponent())
			{
				Player->GetPackageComponent()->RemoveWeaponFromPackage(WeaponUserWidget->GetWeaponSite());
			}
		}
	}
	if (UQuickUseUserWidget* QuickUseUserWidget = Cast<UQuickUseUserWidget>(InOperation->Payload))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
		{
			if (Player->GetPackageComponent())
			{
				Player->GetPackageComponent()->RemovePropsFromSocket(QuickUseUserWidget->GetQuickUse());
			}
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}



void UPackageUserWidget::OnNearItemEnter(ASceneItem* SceneItem) const
{
	if (NearItemScoller)
	{
		NearItemScoller->AddItemUserWidget(SceneItem);
	}
}

void UPackageUserWidget::OnNearItemLeave(ASceneItem* SceneItem) const
{
	if (NearItemScoller)
	{
		NearItemScoller->RemoveItemUserWidget(SceneItem);
	}
}

void UPackageUserWidget::OnAddItemToPackage(int32 Site, FIDAndType IDAndType) const
{
	if (PackageItemScoller)
	{
		PackageItemScoller->AddItemUserWidget(Site,IDAndType);
	}
}

void UPackageUserWidget::OnRemoveItemFromPackage(int32 Site, FIDAndType IDAndType) const
{
	if (PackageItemScoller)
	{
		PackageItemScoller->RemoveItemUserWidget(Site);
	}
}

void UPackageUserWidget::PutinSkin(ESkinType SkinType,int32 ID)
{
	if (SkinVerticalBox)
	{
		for (auto i=0;i<SkinVerticalBox->GetChildrenCount();i++)
		{
			if (USkinSocketUserWidget* SkinUserWidget = Cast<USkinSocketUserWidget>(SkinVerticalBox->GetChildAt(i)))
			{
				if (SkinUserWidget->GetSkinType() == SkinType)
				{
					OnScreenWidgetClose.AddUObject(SkinUserWidget,&USkinSocketUserWidget::RemoveDescribe);
					SkinUserWidget->UpdateIcon(ID);
					break;
				}
			}
		}
	}
}

void UPackageUserWidget::TakeOffSkin(ESkinType SkinType, int32 ID)
{
	if (SkinVerticalBox)
	{
		for (int32 i = 0;i<SkinVerticalBox->GetChildrenCount();i++)
		{
			if (USkinSocketUserWidget* SkinUserWidget = Cast<USkinSocketUserWidget>(SkinVerticalBox->GetChildAt(i)))
			{
				if (SkinUserWidget->GetSkinType() == SkinType)
				{
					OnScreenWidgetClose.RemoveAll(SkinUserWidget);
					SkinUserWidget->UpdateIcon(ID);
					break;
				}
			}
		}
	}
}

USkinSocketUserWidget* UPackageUserWidget::FindWidgetFromType(ESkinType SkinType)
{
	if (SkinVerticalBox)
	{
		for (int32 i = 0;i<SkinVerticalBox->GetChildrenCount();i++)
		{
			if (USkinSocketUserWidget* SkinUserWidget = Cast<USkinSocketUserWidget>(SkinVerticalBox->GetChildAt(i)))
			{
				if (SkinUserWidget->GetSkinType() == SkinType)
				{
					return SkinUserWidget;
				}
			}
		}
	}
	return nullptr;
}

UBoundKeyUserWidget* UPackageUserWidget::FindWidgetFromQuickUse(EQuickUse QuickUse)
{
	if (PropsVerticalBox)
	{
		for (auto _BoundUI:PropsVerticalBox->GetAllChildren())
		{
			if (UBoundKeyUserWidget* BoundUI = Cast<UBoundKeyUserWidget>(_BoundUI))
			{
				if (BoundUI->GetQuickUse() == QuickUse)
				{
					return BoundUI;
				}
			}
		}
	}
	return nullptr;
}

void UPackageUserWidget::AddWeaponToPackage(int32 Site, FWeaponMsg WeaponMsg)
{
	if (WeaponSocket)
	{
		for (auto _WeaponUI : WeaponSocket->GetAllChildren())
		{
			if (UWeaponUserWidget* WeaponUI = Cast<UWeaponUserWidget>(_WeaponUI))
			{
				if (WeaponUI->GetWeaponSite() == Site)
				{
					OnScreenWidgetClose.AddUObject(WeaponUI,&UWeaponUserWidget::RemoveDescribe);
					WeaponUI->UpdateMsg(WeaponMsg);
				}
			}
		}
	}
}

void UPackageUserWidget::RemoveWeaponFromPackage(int32 Site, FWeaponMsg WeaponMsg)
{
	if (WeaponSocket)
	{
		for (auto _WeaponUI : WeaponSocket->GetAllChildren())
		{
			if (UWeaponUserWidget* WeaponUI = Cast<UWeaponUserWidget>(_WeaponUI))
			{
				if (WeaponUI->GetWeaponSite() == Site)
				{
					OnScreenWidgetClose.RemoveAll(WeaponUI);
					WeaponUI->RemoveMsg();
				}
			}
		}
	}
}

void UPackageUserWidget::ExChangeWeapon(int32 Site1, int32 Site2)
{
	if (WeaponSocket)
	{
		UWeaponUserWidget* WeaponUI1 = nullptr;
		UWeaponUserWidget* WeaponUI2 = nullptr;
		for (const auto _WeaponUI : WeaponSocket->GetAllChildren())
		{
			if (UWeaponUserWidget* WeaponUI = Cast<UWeaponUserWidget>(_WeaponUI))
			{
				if (WeaponUI->GetWeaponSite() == Site1)
				{
					WeaponUI1 = WeaponUI;
				}
				else if (WeaponUI->GetWeaponSite() == Site2)
				{
					WeaponUI2 = WeaponUI;
				}
			}
		}
		if (WeaponUI1 && WeaponUI2)
		{
			FWeaponMsg TWeaponMsg = WeaponUI1->GetWeaponMsg();
			WeaponUI1->UpdateMsg(WeaponUI2->GetWeaponMsg());
			WeaponUI2->UpdateMsg(TWeaponMsg);
		}
	}
}

void UPackageUserWidget::BoundProps(EQuickUse Out_QuickUse, int32 Out_Site,int32 Out_ID)
{
	if (PropsVerticalBox)
	{
		//UItemUserWidget* ItemUserWidget = PackageItemScoller->FindWidgetFromSite(Out_Site);
		for (auto Widget:PropsVerticalBox->GetAllChildren())
		{
			if (UQuickUseUserWidget* QuickUseWidget = Cast<UQuickUseUserWidget>(Widget))
			{
				if (QuickUseWidget->GetQuickUse() == Out_QuickUse)
				{
					QuickUseWidget->UpdateMessage(Out_ID,Out_Site);
				}
			}
		}
	}
}

void UPackageUserWidget::UnBoundProps(EQuickUse Out_QuickUse, int32 Out_Site,int32 Out_ID)
{
	if (PropsVerticalBox)
	{
		for (auto Widget:PropsVerticalBox->GetAllChildren())
		{
			if (UQuickUseUserWidget* QuickUseWidget = Cast<UQuickUseUserWidget>(Widget))
			{
				if (QuickUseWidget->GetQuickUse() == Out_QuickUse)
				{
					QuickUseWidget->UpdateMessage(-1,-1);
				}
			}
		}
	}
}

void UPackageUserWidget::ReloadWeaponWidget()
{
	if (WeaponSocket)
	{
		for (auto Widget : WeaponSocket->GetAllChildren())
		{
			if (UWeaponUserWidget* WeaponUserWidget = Cast<UWeaponUserWidget>(Widget))
			{
				WeaponUserWidget->Reload();
			}
		}
	}
}
void UPackageUserWidget::ReloadSkinWidget()
{
	if (SkinVerticalBox)
	{
		for (auto Widget : SkinVerticalBox->GetAllChildren())
		{
			if (USkinSocketUserWidget* SocketUserWidget = Cast<USkinSocketUserWidget>(Widget))
			{
				SocketUserWidget->Reload();
			}
		}
	}
}

void UPackageUserWidget::ReloadPropsWidget()
{
	if (PropsVerticalBox)
	{
		for (auto PropsWidget:PropsVerticalBox->GetAllChildren())
		{
			if (UQuickUseUserWidget* UseWidget = Cast<UQuickUseUserWidget>(PropsWidget))
			{
				UseWidget->Reload();
			}
		}
	}
}





