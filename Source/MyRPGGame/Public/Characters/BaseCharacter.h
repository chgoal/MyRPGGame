// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Subsystem/WeaponSubsystem.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Interface/PackageInterface.h"
#include "Interface/SkinInterface.h"
#include "BaseCharacter.generated.h"

class USaveGame;
enum class EHitDirection : uint8;
class UCharacterAttributeSet;
class UWidgetComponent;
struct FGameplayTag;
class UAttributeComponent;
class UCameraComponent;
class USpringArmComponent;
class UPackageComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(NotifyDamage,float)//用于传递伤害给UMG
UENUM()
enum class ETeamColor:uint8
{
	ETC_Green,
	ETC_Yellow,
	ETC_Red
};

UENUM(BlueprintType)
enum class EWeaponHide:uint8//顺序V表示可视，H表示隐藏
{
	EWH_VV,
	EWH_VH,
	EWH_HV,
	EWH_HH
};
// class UAbilitySystemComponent;
UCLASS()
class MYRPGGAME_API ABaseCharacter : public ACharacter,public IAbilitySystemInterface,public ISkinInterface,public IPackageInterface,public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual USkinComponent* GetSkinComponent() override;
	virtual USkeletalMeshComponent* GetSkinSkeletalMeshComponent() override;
	virtual UPackageComponent* GetCharacterPackageComponent() override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	virtual void LoadSave(USaveGame* SaveGame);


protected:
	//组件
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category= "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USkinComponent* SkinComponent;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UPackageComponent* PackageComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UWidgetComponent* HeadWidgetComponent;
	UPROPERTY(BlueprintReadOnly)
	UCharacterAttributeSet* CharacterAttribute;
	// UPROPERTY(EditAnywhere)
	// UAttributeComponent* AttributeComponent;

	//攻击参数
	UPROPERTY()
	float FullAttackPower;
	UPROPERTY()
	float FullDefencePower;
	
	//参数
	float HitYaw;
	UPROPERTY(BlueprintReadWrite)
	bool bWidgetOpen;//记录有没有打开UI
	UPROPERTY(BlueprintReadWrite)
	bool Equip;//装备
	bool Crouch;//蹲着
	bool bSprite;//冲刺
	UPROPERTY(BlueprintReadWrite)
	bool bIsAlive;
	UPROPERTY(BlueprintReadWrite)
	float MoveX;
	UPROPERTY(BlueprintReadWrite)
	float MoveY;
	UPROPERTY(BlueprintReadWrite)
	float CMoveX;
	UPROPERTY(BlueprintReadWrite)
	float CMoveY;
	UPROPERTY(BlueprintReadWrite)
	bool bInvincibility;//无敌状态
	UPROPERTY(BlueprintReadWrite)
	bool bHurt;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MoveMent|Speed")
	//冲刺时的速度
	float SpriteSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "MoveMent|Speed")
	//正常时候的速度
	float WalkSpeed;
	UPROPERTY(EditAnywhere,Category="Abilities")
	int32 CharacterLevel;
	
	//结构体
	UPROPERTY(BlueprintReadOnly)
	EHitDirection HitDirection;
	EWeaponState WeaponState;
	UPROPERTY(EditAnywhere,Category="Team")
	ETeamColor TeamColor;
	///STL组件
	//GA的Ability内容
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> PreloadedAbilities;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> PreloadedEffects;
	// UPROPERTY(EditAnywhere)
	// TArray<USkeletalMeshComponent*> SkeletalComponents;//记录子类
	//资产
	UPROPERTY()
	UCharacterAttributeSet* CharacterAttributesSet;
	
	
public:

	//特殊变量
	NotifyDamage OnDamage;
	//保存GameplayTags
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Abilities")
	FGameplayTag WeaponGameplayTag;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Abilities")
	//用于存角色状态
	FGameplayTagContainer TagContainer;
	//移动以及攻击
	UFUNCTION()
	void MoveForward(float Axis);
	UFUNCTION()
	void MoveRight(float Axis);
	UFUNCTION()
	void DoSprite();
	UFUNCTION()
	void GotDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser,FHitResult Result);

	//一些代理绑定
	void EquipWeapon(FWeaponMsg WeaponMsg);
	void UnEquipWeapon(FWeaponMsg WeaponMsg);
	
	//外界获取或修改信息
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UPackageComponent* GetPackageComponent();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	EWeaponState GetWeaponState();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	ETeamColor GetTeamColor();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<USceneComponent*> GetMainSkeletalMeshAttachChild() const;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void SetWeaponState(EWeaponState Out_WeaponState);
	UFUNCTION(BlueprintCallable)
	void SetHurt(bool Out_bHurt);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetHurt();
	UFUNCTION(BlueprintCallable)
	void SetInvincibility(bool Out_Invincibility);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetInvincibility();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetMoveX();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetMoveY();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetFullAttack();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetFullDefence();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	EHitDirection GetHitDirection();
	UFUNCTION(BlueprintCallable)
	int32 GetCharacterLevel() const;
	
	///一些功能函数
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ReceiveDamage();
	UFUNCTION(BlueprintCallable)
	void MakeDamage(float Damage);
	UFUNCTION()
	EHitDirection CalHitDirection();

	//存档加载
	UFUNCTION()
	virtual void SaveLoad(USaveGame* SaveGame);
	
	//GameplayAbility
	void WeaponGameplayTags();
	UFUNCTION(BlueprintCallable)
	FGameplayTag AddedWeaponGameplayTags( FGameplayTag OutGameplayTag,FString AddedTag = TEXT(""));
	//初始化内容
	virtual void BGInitParams();
	void ConInitParams();
	//加载GA
	void PreloadAbility();
	UFUNCTION(BlueprintCallable,Category= "Ability System")
	//重写GiveAbility使蓝图可以调用
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability,int32 level = 1);

	//数据表内容
	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHeath() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetMana() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxMana() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetStamina() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxStamina() const;
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHeath); 
	//开权限
	friend class UTargetComponent;
	friend class UBaseAnimInstance;

};

inline void ABaseCharacter::SetInvincibility(bool Out_Invincibility)
{
	bInvincibility = Out_Invincibility;
}
inline bool ABaseCharacter::GetInvincibility()
{
	return bInvincibility;
}
inline float ABaseCharacter::GetMoveX()
{
	return MoveX;
}
inline float ABaseCharacter::GetMoveY()
{
	return MoveY;
}
