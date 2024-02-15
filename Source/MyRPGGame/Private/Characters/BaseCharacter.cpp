// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRPGGame/Public/Characters/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
//#include "BlueprintGameplayTagLibrary.h"
#include "GameplayTagContainer.h"
//#include "ActorComponent/AttributeComponent.h"
#include "ActorComponent/SkinComponent.h"
#include "ActorComponent/PackageComponent.h"
#include "Actors/Weapon.h"
#include "Anim/BaseAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Controller/BaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyRPGGame/MyRPGGame.h"
#include "Data/Attribute/CharacterAttributeSet.h"
#include "SaveGame/MyRPGSaveGame.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CamComp"));
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySys"));
	SkinComponent = CreateDefaultSubobject<USkinComponent>(TEXT("SkinComp"));
	PackageComponent = CreateDefaultSubobject<UPackageComponent>(TEXT("PackageComp"));
	HeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadWiget"));
	CharacterAttribute = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("AttributeSet"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
	HeadWidgetComponent->SetupAttachment(GetMesh());
	ConInitParams();
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	if (SkinComponent)
	{
		PackageComponent->OnSkinPuton.AddUObject(SkinComponent,&USkinComponent::PutinSkin);
        PackageComponent->OnSkinTakeOff.AddUObject(SkinComponent,&USkinComponent::TakeOffSkin);
        PackageComponent->OnWeaponEquip.AddUObject(SkinComponent,&USkinComponent::EquipWeapon);
        PackageComponent->OnWeaponUnEquip.AddUObject(SkinComponent,&USkinComponent::UnEquipWeapon);
        PackageComponent->OnWeaponRemoveAll.AddUObject(SkinComponent,&USkinComponent::UnEquipWeapon);
        PackageComponent->OnSkinRemoveAll.AddUObject(SkinComponent,&USkinComponent::TakeOffAllSkin);
	}
	PackageComponent->OnWeaponEquip.AddUObject(this,&ABaseCharacter::EquipWeapon);
	PackageComponent->OnWeaponUnEquip.AddUObject(this,&ABaseCharacter::UnEquipWeapon);
	Super::BeginPlay();
	BGInitParams();
	PreloadAbility();
	
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

USkinComponent* ABaseCharacter::GetSkinComponent()
{
	return SkinComponent;
}

USkeletalMeshComponent* ABaseCharacter::GetSkinSkeletalMeshComponent()
{
	return GetMesh();
}

UPackageComponent* ABaseCharacter::GetCharacterPackageComponent()
{
	return PackageComponent;
}

FGenericTeamId ABaseCharacter::GetGenericTeamId() const
{
	if (TeamColor == ETeamColor::ETC_Green)
	{
		return TeamID_Green;
	}
	if (TeamColor == ETeamColor::ETC_Yellow)
	{
		return TeamID_Yellow;
	}
	return TeamID_Red;
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	ReceiveDamage();
	
	//MakeDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseCharacter::Destroyed()
{
	if (SkinComponent->GetWeapon(true))
	{
		SkinComponent->GetWeapon(true)->Destroy();
	}
	if (SkinComponent->GetWeapon(false))
	{
		SkinComponent->GetWeapon(false)->Destroy();
	}
	Super::Destroyed();
}

void ABaseCharacter::LoadSave(USaveGame* SaveGame)
{
	
}
// UAttributeComponent* ABaseCharacter::GetAttributeComponent()
// {
// 	return AttributeComponent;
// }

void ABaseCharacter::BGInitParams()
{
	if (WalkSpeed <= 0.f)
	{
		WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	}
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	for (auto AttributeSet:GetAbilitySystemComponent()->GetSpawnedAttributes())
	{
		if (UCharacterAttributeSet* Attribute = Cast<UCharacterAttributeSet>(AttributeSet))
		{
			CharacterAttributesSet = Attribute;
			
		}
	}
}

void ABaseCharacter::ConInitParams()
{
	bWidgetOpen = false;
	bIsAlive = true;
}



void ABaseCharacter::MoveForward(float Axis)
{
	AddMovementInput(FRotator(0,GetControlRotation().Yaw,0).Quaternion().GetAxisX(),Axis);

	CMoveY = Axis;

}

void ABaseCharacter::MoveRight(float Axis)
{
	AddMovementInput(FRotator(0,GetControlRotation().Yaw,0).Quaternion().GetAxisY(),Axis);
	CMoveX = Axis;

}

void ABaseCharacter::DoSprite()
{
	if (bSprite)
	{
		GetCharacterMovement()->MaxWalkSpeed = SpriteSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	
}

void ABaseCharacter::GotDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser, FHitResult Result)
{
	 float RealDamage;
	if (!bInvincibility)//在非无敌状态下受到伤害
 	{
	    RealDamage = Damage-FullDefencePower;
		TakeDamage(RealDamage,DamageEvent,EventInstigator,DamageCauser);
		HitYaw = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(),UKismetMathLibrary::FindLookAtRotation(Result.TraceEnd,Result.TraceStart)).Yaw;
		HitDirection = CalHitDirection();
	    bHurt = true;
	    if (ABaseAIController* BaseAIController = Cast<ABaseAIController>(GetController()))
    	{
    		if (BaseAIController->GetBlackboardComponent())
    		{
    			BaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("Hit"),bHurt);
    		}
    	}
 	}
}

void ABaseCharacter::EquipWeapon(FWeaponMsg WeaponMsg)
{
	FullAttackPower = CharacterAttributesSet->GetAttackPower();
	FullDefencePower = CharacterAttributesSet->GetDefencePower();
	if (WeaponMsg.ID!=-1)
	{
		if (const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponSubsystem>()->GetWeaponsByID(WeaponMsg.ID))
		{
			if (const FWeapons* Weapons = static_cast<const FWeapons*>(PropsBase))
			{
				SetWeaponState(Weapons->WeaponState);
				WeaponGameplayTags();
			}
		}
		
	}
}

void ABaseCharacter::UnEquipWeapon(FWeaponMsg WeaponMsg)
{
	if (WeaponMsg.ID == -1)
	{
		SetWeaponState(EWeaponState::EWS_None);
		
	}
}


float ABaseCharacter::GetFullAttack()
{
	return FullAttackPower;
}

float ABaseCharacter::GetFullDefence()
{
	return FullDefencePower;
}

EHitDirection ABaseCharacter::GetHitDirection()
{
	return HitDirection;
}

int32 ABaseCharacter::GetCharacterLevel() const
{
	return CharacterLevel;
}

void ABaseCharacter::MakeDamage(float Damage)
{
	CharacterAttribute->SetHealth(CharacterAttribute->GetHealth()-Damage);
}

EHitDirection ABaseCharacter::CalHitDirection()
{
	
	if (HitYaw<=45 && HitYaw>=-45)
	{
		return EHitDirection::EHD_Forward;
	}
	if (HitYaw>=45 && HitYaw<=150)
	{
		return EHitDirection::EHD_Right;
	}
	if (HitYaw<=-45 && HitYaw>=-150)
	{
		return EHitDirection::EHD_Left;
	}
	return EHitDirection::EHD_Backward;
}

void ABaseCharacter::SaveLoad(USaveGame* SaveGame)
{
	if (UMyRPGSaveGame* MyRPGSaveGame = Cast<UMyRPGSaveGame>(SaveGame))
	{
		
	}	
}

void ABaseCharacter::WeaponGameplayTags()
{
	
	switch (WeaponState)
	{
	case EWeaponState::EWS_Knight:
		{
			//GameplayTags.Empty();
			WeaponGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Ability.Player.Knight"));
			break;
		}
	case EWeaponState::EWS_Gun:
		{
			// GameplayTags.Empty();
			// GameplayTags.Add(FGameplayTag::RequestGameplayTag("Ability.Player.Gun"));
			WeaponGameplayTag = FGameplayTag::RequestGameplayTag("Ability.Player.Gun");
			break;
		}
		
	case EWeaponState::EWS_Spear:
		{
			// GameplayTags.Empty();
			// GameplayTags.Add(FGameplayTag::RequestGameplayTag("Ability.Player.Spear"));
			WeaponGameplayTag = FGameplayTag::RequestGameplayTag("Ability.Player.Spear");
			break;
		}
	case EWeaponState::EWS_None:
		{
			// GameplayTags.Empty();
			WeaponGameplayTag = FGameplayTag::EmptyTag;
			break;
		}
		default:break;
	}
}




FGameplayTag ABaseCharacter::AddedWeaponGameplayTags(FGameplayTag OutGameplayTag,FString AddedTag)
{
	if (AddedTag == TEXT(""))
	{
		return OutGameplayTag;
	}
	if (!AddedTag.StartsWith("."))
	{
		FString Dot = TEXT(".");
		AddedTag = Dot.Append(AddedTag);
	}
	FString Tag = OutGameplayTag.ToString().Append(AddedTag);
	return FGameplayTag::RequestGameplayTag(*Tag);
}

UPackageComponent* ABaseCharacter::GetPackageComponent()
{
	return PackageComponent;
}

EWeaponState ABaseCharacter::GetWeaponState()
{
	return WeaponState;
}

ETeamColor ABaseCharacter::GetTeamColor()
{
	return TeamColor;
}

void ABaseCharacter::SetWeaponState(EWeaponState Out_WeaponState)
{
	WeaponState = Out_WeaponState;
}

void ABaseCharacter::SetHurt(bool Out_bHurt)
{
	bHurt = Out_bHurt;
	if (ABaseAIController* BaseAIController = Cast<ABaseAIController>(GetController()))
	{
		if (BaseAIController->GetBlackboardComponent())
		{
			BaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("Hit"),bHurt);
		}
	}
}

bool ABaseCharacter::GetHurt()
{
	return bHurt;
}




TArray<USceneComponent*> ABaseCharacter::GetMainSkeletalMeshAttachChild() const
{
	return GetMesh()->GetAttachChildren();
}



UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}



void ABaseCharacter::PreloadAbility()
{
	if (PreloadedAbilities.Num()>0)
	{
		for (auto i = 0;i<PreloadedAbilities.Num();i++)
		{
			if (PreloadedAbilities[i] != nullptr)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(PreloadedAbilities[i].GetDefaultObject(),1));
			}
		}
	}
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : PreloadedEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,GetCharacterLevel(),EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(),AbilitySystemComponent);
		}
	}
	TArray<UAttributeSet*> Attributeses;
	Attributeses.AddUnique(CharacterAttribute);
	AbilitySystemComponent->SetSpawnedAttributes(Attributeses);
}

void ABaseCharacter::GiveAbility(TSubclassOf<UGameplayAbility> Ability, int32 level)
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && Ability)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability,level));
		}
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

float ABaseCharacter::GetHealth() const
{
	if (!CharacterAttribute)
	{
		return 1.f;
	}
	return CharacterAttribute->GetHealth();
}

float ABaseCharacter::GetMaxHeath() const
{
	return CharacterAttribute->GetMaxHealth();
}

float ABaseCharacter::GetMana() const
{
	return CharacterAttribute->GetMana();
}

float ABaseCharacter::GetMaxMana() const
{
	return CharacterAttribute->GetMaxMana();
}

float ABaseCharacter::GetStamina() const
{
	return CharacterAttribute->GetStamina();
}

float ABaseCharacter::GetMaxStamina() const
{
	return CharacterAttribute->GetMaxStamina();
}

void ABaseCharacter::SetHealth(float NewHeath)
{
	CharacterAttribute->SetHealth(NewHeath);
}




