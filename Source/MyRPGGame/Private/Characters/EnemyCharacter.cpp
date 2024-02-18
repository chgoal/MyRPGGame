// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRPGGame/Public/Characters/EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "ActorComponent/SkinComponent.h"
#include "Actors/SceneActor.h"
#include "Actors/Weapon.h"
#include "UMG/AimUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	// WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp"));
	// BackWeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackWeaponComp"));
	// WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// BackWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// WeaponComponent->SetupAttachment(GetMesh());
	// BackWeaponComponent->SetupAttachment(GetMesh());
	Initialize();
	AnimPlay = false;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponSocketName = TEXT("Sword");
	BackWeaponSocketName = TEXT("BackSword");
	BeginInitialize();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AEnemyCharacter::BgSpawn,0.6f);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (EventInstigator)
	{
		if (OnDamage.IsBound())
		{
			OnDamage.Broadcast(DamageAmount);
		}
		//AbilitySystemComponent->TryActivateAbilitiesByTag()
	}
	if (!TagContainer.HasTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Enemy.Die"))))
	{
		MakeDamage(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemyCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	// if (!SkinComponent->GetWeapon(true))
	// {
	// 	if (MainWeapon)
	// 	{
	// 		if (MainWeapon->GetClass())
	// 		{
	// 			UE_LOG(LogTemp, Log, TEXT("MainWeapon"))
	// 			SkinComponent->EquipWeapon(MainWeapon,WeaponSocketName);
	// 		}
	// 	}
	// }
	// if (!SkinComponent->GetWeapon(false))
	// {
	// 	if (OffWeapon)
	// 	{
	// 		if (OffWeapon->GetClass())
	// 		{
	// 			SkinComponent->EquipWeapon(OffWeapon,BackWeaponSocketName,false);
	// 		}
	// 	}
	// }
}

void AEnemyCharacter::Select()
{
	if (ActiveTargetWidget == nullptr)
	{
		ActiveTargetWidget = CreateWidget<UAimUserWidget>(GetWorld(),TargetBarWidgetClass);
		if (ActiveTargetWidget)
		{
			ActiveTargetWidget->AttachedActor = this;//设置函数
			ActiveTargetWidget->AddToViewport();
		}
	}
	else
	{
		ActiveTargetWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AEnemyCharacter::CancelSelect()
{
	if (ActiveTargetWidget)
	{
		ActiveTargetWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AEnemyCharacter::Destroyed()
{
	if (GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->DestroyItem(EnemyID);
	}
	Super::Destroyed();
}

UAimUserWidget* AEnemyCharacter::GetTargetWidget() const
{
	return ActiveTargetWidget;
}

void AEnemyCharacter::Initialize()
{
	FindEnemy = CreateDefaultSubobject<UWidgetComponent>(TEXT("FindEnemyWidget"));
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Sight"));
	
	FindEnemy->SetupAttachment(GetMesh());
	DecalComponent->SetupAttachment(CameraComponent);
}

void AEnemyCharacter::BgSpawn()
{
	if (UWeaponSubsystem* WeaponSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>())
	{
		if (WeaponSubsystem->Check_IfDestroyed(EnemyID))
		{
			Destroy();
		}
	}
}

void AEnemyCharacter::BeginInitialize()
{
	if (!SkinComponent->GetWeapon(true))
	{
		if (MainWeapon)
		{
			if (MainWeapon->GetClass())
			{
				SkinComponent->EquipWeapon(MainWeapon,WeaponSocketName);
			}
		}
	}
	if (!SkinComponent->GetWeapon(false))
	{
		if (OffWeapon)
		{
			if (OffWeapon->GetClass())
			{
				SkinComponent->EquipWeapon(OffWeapon,BackWeaponSocketName,false);
			}
		}
	}
	UnEquipWeapon();
}

void AEnemyCharacter::SetWeaponVisibility(EWeaponHide HideState)
{
	if (!SkinComponent->GetWeapon(true))
	{
		return;
	}
	if (!SkinComponent->GetWeapon(false))
	{
		return;
	}
	switch (HideState)
	{
	case EWeaponHide::EWH_HH:
		{
			SkinComponent->GetWeapon(true)->HideWeapon(false);
			SkinComponent->GetWeapon(false)->HideWeapon(false);
			break;
		}
	case EWeaponHide::EWH_HV:
		{
			SkinComponent->GetWeapon(true)->HideWeapon(false);
			SkinComponent->GetWeapon(false)->HideWeapon(true);
			break;
		}
	case EWeaponHide::EWH_VH:
		{
			SkinComponent->GetWeapon(true)->HideWeapon(true);
			SkinComponent->GetWeapon(false)->HideWeapon(false);
			break;
		}
	case EWeaponHide::EWH_VV:
		{
			SkinComponent->GetWeapon(true)->HideWeapon(true);
			SkinComponent->GetWeapon(false)->HideWeapon(true);
			break;
		}
		default:break;
	}
}

void AEnemyCharacter::EquipWeapon()
{
	SetWeaponVisibility(EWeaponHide::EWH_VH);
}

void AEnemyCharacter::UnEquipWeapon()
{
	 SetWeaponVisibility(EWeaponHide::EWH_HV);
}













