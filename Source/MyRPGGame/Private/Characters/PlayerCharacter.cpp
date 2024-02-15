// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRPGGame/Public/Characters/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Actors/SceneItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorComponent/PackageComponent.h"
#include "ActorComponent/TargetComponent.h"
#include "Camera/CameraComponent.h"
#include "SaveGame/MyRPGSaveGame.h"
#include "UMG/PackageUserWidget.h"
#include "UMG/PlayerHUD.h"

APlayerCharacter::APlayerCharacter()
{
	//初始化组件
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PackageSphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	SphereComponent->SetSphereRadius(150.f);
	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComp"));
	

	
	//初始化变量
	//移动相关
	PrimaryActorTick.bCanEverTick = true;
	bLockOn = false;
	bStartCombo = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->bUsePawnControlRotation = true;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::OnSphereComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&APlayerCharacter::OnSphereComponentEndOverlap);
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//轴映射
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&APlayerCharacter::LookUP);
	PlayerInputComponent->BindAxis(TEXT("LookAround"),this,&APlayerCharacter::LookAround);
	//操作映射
	PlayerInputComponent->BindAction(TEXT("DoJump"),IE_Pressed,this,&APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("DoLockOn"),IE_Pressed,this,&APlayerCharacter::DoLockOn);
	// PlayerInputComponent->BindAction(TEXT("DoSprite"),IE_Pressed,this,&APlayerCharacter::StartSprite);
	// PlayerInputComponent->BindAction(TEXT("DoSprite"),IE_Released,this,&APlayerCharacter::StopSprite);
	PlayerInputComponent->BindAction(TEXT("TogglePackage"),IE_Pressed,this,&APlayerCharacter::TogglePackage);
	PlayerInputComponent->BindAction(TEXT("ToggleMainMenu"),IE_Pressed,this,&APlayerCharacter::ToggleMainMenu);
	PlayerInputComponent->BindAction(TEXT("PropertyPanel1"),IE_Pressed,this,&APlayerCharacter::FirstQuickUse);
	PlayerInputComponent->BindAction(TEXT("PropertyPanel2"),IE_Pressed,this,&APlayerCharacter::SecondQuickUse);
	PlayerInputComponent->BindAction(TEXT("Testing"),IE_Pressed,this,&APlayerCharacter::ForTesting);

	
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const FGameplayTagContainer GameplayTags(FGameplayTag::RequestGameplayTag(TEXT("Ability.Player.Hit.Physical")));
	AbilitySystemComponent->TryActivateAbilitiesByTag(GameplayTags);
	//PrintAttribute();
	if (!TagContainer.HasTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Player.Sword.Shield"))) &&
		!TagContainer.HasTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Player.Death"))))
	{
		MakeDamage(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

FVector APlayerCharacter::GetPawnViewLocation() const
{
	return CameraComponent->GetComponentLocation();
}

void APlayerCharacter::LoadSave(USaveGame* SaveGame)
{
	if (UMyRPGSaveGame* MyRPGSaveGame = Cast<UMyRPGSaveGame>(SaveGame))
	{
		SetActorLocation(MyRPGSaveGame->CharacterLocation);
		SetActorRotation(MyRPGSaveGame->CharacterRotator);
		if (PackageComponent)
		{
			PackageComponent->LoadPackage(MyRPGSaveGame->PackageItem,MyRPGSaveGame->SkinMapItem,MyRPGSaveGame->PropsMapItem,MyRPGSaveGame->WeaponMapItem);
		}
	}
	Super::LoadSave(SaveGame);
}

void APlayerCharacter::LookUP(float Axis)
{
	if (!bLockOn)
	{
		AddControllerPitchInput(Axis*GetWorld()->GetDeltaSeconds()*-35);
	}
}

void APlayerCharacter::LookAround(float Axis)
{
	if (!bLockOn)
	{
		AddControllerYawInput(Axis* GetWorld()->GetDeltaSeconds()*35);
	}	
}

void APlayerCharacter::LockRotator()
{
}

void APlayerCharacter::FirstQuickUse()
{
	if (!bWidgetOpen)
	{
		UseProps(EQuickUse::EQU_QuickUse1);
	}
	
}

void APlayerCharacter::SecondQuickUse()
{
	if (!bWidgetOpen)
	{
		UseProps(EQuickUse::EQU_QuickUse2);
	}
	
}

// void APlayerCharacter::StartSprite()
// {
// 	if (!bWidgetOpen)
// 	{
// 		bSprite = true;
// 	}
// }

// void APlayerCharacter::StopSprite()
// {
// 	if (!bWidgetOpen)
// 	{
// 		bSprite = false;
// 	}
// 	
// }


void APlayerCharacter::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASceneItem* SceneItem = Cast<ASceneItem>(OtherActor))
	{
		if (PackageComponent)
		{
			PackageComponent->AddNearItem(SceneItem);
		}
	}
}

void APlayerCharacter::OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ASceneItem* SceneItem = Cast<ASceneItem>(OtherActor))
	{
		if (PackageComponent)
		{
			PackageComponent->RemoveNearItem(SceneItem);
		}
	}
}

void APlayerCharacter::TogglePackage()//用于打开背包
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (APlayerHUD* HUD = Cast<APlayerHUD>(PC->GetHUD()))
		{
			bWidgetOpen = HUD->TogglePackage();
		}
	}
}

void APlayerCharacter::ToggleMainMenu()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (APlayerHUD* HUD = Cast<APlayerHUD>(PC->GetHUD()))
		{
			HUD->ToggleMainMenu();//暂停记号
		}
	}
}

bool APlayerCharacter::GetbLockOn()
{
	return bLockOn;
}

void APlayerCharacter::SetLockOn(bool Out_bLockOn)
{
	bLockOn = Out_bLockOn;
}

void APlayerCharacter::SetLeftAttackCount(int32 Count)
{
	LeftAttackCount = Count;
}

int32 APlayerCharacter::GetLeftAttackCount()
{
	return LeftAttackCount;
}

void APlayerCharacter::SetStartCombo(bool Out_StartCombo)
{
	bStartCombo = Out_StartCombo;
}

bool APlayerCharacter::GetStartCombo()
{
	return bStartCombo;
}

void APlayerCharacter::SetRightAttack(bool Out_RightAttack)
{
	if (!bWidgetOpen)
	{
		bRightAttack = Out_RightAttack;
	}
	
}

bool APlayerCharacter::GetRightAttack()
{
	return bRightAttack;
}

void APlayerCharacter::SetSprite(bool Out_bSprite)
{
	if (!bWidgetOpen)
	{
		bSprite = Out_bSprite;
	}
	
}


void APlayerCharacter::ResetAttack()
{
	bLeftAttack = false;
	bSaveLeftAttack = false;
	bStartCombo = false;
	LeftAttackCount = 0;
}

void APlayerCharacter::ForTesting()
{
	UE_LOG(LogTemp, Log, TEXT("Testing"))
	GetPackageComponent()->PrintPackageItem();
}

void APlayerCharacter::DoLockOn()
{
	TargetComponent->FindTarget();
}

void APlayerCharacter::UseProps(int32 Site)
{
	int32 MID = GetPackageComponent()->GetPackageItemFromSite(Site).ID;
	if (MID==-1)
	{
		return;	
	}
	const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetPropsByID(MID);
	if (!PropsBase)
	{
		return;
	}
	if (const FProps* Props = static_cast<const FProps*>(PropsBase))
	{
		//GiveAbility(Props->AddPropsGameAbility);
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(Props->AddPropsGameAbility.GetDefaultObject()->AbilityTags);
		GetPackageComponent()->UseProps(Site);
	}
	
}

void APlayerCharacter::UseProps(EQuickUse QuickUse)
{
	int32 Site = GetPackageComponent()->GetSiteFromPropsMap(QuickUse);
	if (Site == -1)
	{
		return;
	}
	UseProps(Site);
}
