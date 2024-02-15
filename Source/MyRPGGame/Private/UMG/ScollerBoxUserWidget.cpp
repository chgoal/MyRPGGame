// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ScollerBoxUserWidget.h"

#include "ActorComponent/PackageComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "Characters/PlayerCharacter.h"
#include "Components/ScrollBox.h"
#include "UMG/ItemUserWidget.h"
#include "UMG/PackageUserWidget.h"
#include "UMG/SkinSocketUserWidget.h"

void UScollerBoxUserWidget::AddItemUserWidget(ASceneItem* SceneItem) const
{
	const TSubclassOf<UItemUserWidget> ItemWidget = LoadClass<UItemUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Item.UI_Item_C'"));
	UItemUserWidget* ItemUserWidget = CreateWidget<UItemUserWidget>(GetOwningPlayer(),ItemWidget);
	if (ItemUserWidget)
	{
		ItemUserWidget->InitPanel(SceneItem);
		ItemUserWidget->SetInPackage(bPackageScrollBox);
		ItemUserWidget->SetPadding(FMargin(0.f,4.f));
		ItemScoller->AddChild(ItemUserWidget);
		if (PackageWidget)
		{
			PackageWidget->OnScreenWidgetClose.AddUObject(ItemUserWidget,&UItemUserWidget::RemoveDescribe);
		}
	}
}

void UScollerBoxUserWidget::RemoveItemUserWidget(ASceneItem* SceneItem) const
{
	for (int32 i = 0;i<ItemScoller->GetChildrenCount();i++)
	{
		if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(ItemScoller->GetChildAt(i)))
		{
			if (ItemUserWidget->GetSceneItem() == SceneItem)
			{
				
				ItemUserWidget->RemoveFromParent();
				
				break;
			}
		}
	}
}

void UScollerBoxUserWidget::AddItemUserWidget(int32 Site, FIDAndType IDAndType)
{
	TSubclassOf<UItemUserWidget> ItemWidget = LoadClass<UItemUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/Projecte/UMG/UI_Item.UI_Item_C'"));
	
	if (UItemUserWidget* Wiget = FindWidgetFromSite(Site))//是道具并且背包里有的话要写重叠的方式
	{
		if (IDAndType.ItemType == EItemType::EPT_Tool)
		{
			Wiget->InitPanel(Site,IDAndType);
		}
	}
	else
	{
		UItemUserWidget* ItemUserWidget = CreateWidget<UItemUserWidget>(GetOwningPlayer(),ItemWidget);
        if (ItemUserWidget)
        {
        	ItemUserWidget->InitPanel(Site,IDAndType);
        	ItemUserWidget->SetPadding(FMargin(0.f,4.f));
        	if (PackageWidget)
        	{
        		PackageWidget->OnScreenWidgetClose.AddUObject(ItemUserWidget,&UItemUserWidget::RemoveDescribe);
        	}
        	ItemScoller->AddChild(ItemUserWidget);
        	//ScollerChild.Add(Site,ItemUserWidget);
        }
	}
	
}

void UScollerBoxUserWidget::RemoveItemUserWidget(int32 Site)
{
	for (int32 i = 0;i<ItemScoller->GetChildrenCount();i++)
	{
		if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(ItemScoller->GetChildAt(i)))
		{
			if (ItemUserWidget->GetItemSite() == Site)
			{
				// if (ScollerChild.Contains(Site))
				// {
				// 	ScollerChild.Remove(Site);
				// }
				if (PackageWidget)
				{
					PackageWidget->OnScreenWidgetClose.RemoveAll(ItemUserWidget);
				}
				ItemUserWidget->RemoveFromParent();
				break;
			}
		}
	}
}

UItemUserWidget* UScollerBoxUserWidget::FindWidgetFromSite(int32 Site)
{
	if (ItemScoller)
	{
		for (auto Widget:ItemScoller->GetAllChildren())
		{
			if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(Widget))
			{
				if (ItemUserWidget->GetItemSite() == Site)
				{
					return ItemUserWidget;
				}
			}
		}
	}
	return nullptr;
}

void UScollerBoxUserWidget::ClearAll() const
{
	if (ItemScoller && ItemScoller->HasAnyChildren())
	{
		ItemScoller->ClearChildren();
	}
}

void UScollerBoxUserWidget::ResetAll() const
{
	if (ItemScoller && ItemScoller->HasAnyChildren())
	{
		for (auto Item:ItemScoller->GetAllChildren())
		{
			if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(Item))
			{
				ItemUserWidget->ResetPanel();
			}
		}
	}
}

void UScollerBoxUserWidget::DeleteAll() const
{
	if (ItemScoller)
	{
		for (auto Item:ItemScoller->GetAllChildren())
		{
			if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(Item))
			{
				ItemUserWidget->RemoveFromParent();
			}
		}
		ItemScoller->ClearChildren();
	}
}

void UScollerBoxUserWidget::Reload()
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
	{
		//TMap<int32,FIDAndType> PackageItem = Character->GetPackageComponent()->GetPackageItem();
		if (ItemScoller)
		{
			TMap<int32,FIDAndType> Package;
			Character->GetPackageComponent()->GetPackageItem(Package);
			DeleteAll();
			for (auto Item:Package)
			{
				//UE_LOG(LogTemp, Log, TEXT("Item.Key = %d,Item.Value= %d"),Item.Key,Item.Value.Number)
				AddItemUserWidget(Item.Key,Item.Value);
			}
		}
	}
}

void UScollerBoxUserWidget::SetPackageWidget(UPackageUserWidget* Out_PackageWidget)
{
	if (!PackageWidget)
	{
		PackageWidget = Out_PackageWidget;
	}
}


bool UScollerBoxUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                         UDragDropOperation* InOperation)
{
	if (!bPackageScrollBox)
	{
		return false;
	}
	if (UItemUserWidget* ItemUserWidget = Cast<UItemUserWidget>(InOperation->Payload))
	{
		if (IPackageInterface* PackageInterface = Cast<IPackageInterface>(GetOwningPlayerPawn()))
		{
			PackageInterface->GetCharacterPackageComponent()->AddItemToPackage(ItemUserWidget->GetSceneItem());
		}
	}
	if (USkinSocketUserWidget* SkinUserWidget = Cast<USkinSocketUserWidget>(InOperation->Payload))
	{
		if (IPackageInterface* PackageInterface = Cast<IPackageInterface>(GetOwningPlayerPawn()))
		{
			PackageInterface->GetCharacterPackageComponent()->TakeOffSkin(SkinUserWidget->GetSkinType());
		}
	}
	if (bPackageScrollBox)
	{
		return true;
	}
	else
	{
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	}
	
}
