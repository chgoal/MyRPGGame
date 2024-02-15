// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Attribute/CharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Characters/BaseCharacter.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Mana = 100.f;
	MaxMana = 100.f;
	Stamina = 100.f;
	MaxStamina = 100.f;
	AttackPower = 10.f;
	DefencePower = 5.f;
	MoveSpeed = 0.f;
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health,MaxHealth,NewValue,GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana,MaxMana,NewValue,GetManaAttribute());
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// Super::PostGameplayEffectExecute(Data);
	// FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	// UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	// const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	//
	// float DeltaValue = 0;
	// if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	// {
	// 	DeltaValue = Data.EvaluatedData.Magnitude;
	// }
	// // Get the Target actor, which should be our owner
	// AActor* TargetActor = nullptr;
	// AController* TargetController = nullptr;
	// ABaseCharacter* TargetCharacter = nullptr;
	// if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	// {
	// 	TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	// 	TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	// 	TargetCharacter = Cast<ABaseCharacter>(TargetActor);
	// }
	//
	// if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	// {
	// 	// Get the Source actor
	// 	AActor* SourceActor = nullptr;
	// 	AController* SourceController = nullptr;
	// 	ABaseCharacter* SourceCharacter = nullptr;
	// 	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	// 	{
	// 		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
	// 		SourceController = Source->AbilityActorInfo->PlayerController.Get();
	// 		if (SourceController == nullptr && SourceActor != nullptr)
	// 		{
	// 			if (APawn* Pawn = Cast<APawn>(SourceActor))
	// 			{
	// 				SourceController = Pawn->GetController();
	// 			}
	// 		}
	//
	// 		// Use the controller to find the source pawn
	// 		if (SourceController)
	// 		{
	// 			SourceCharacter = Cast<ABaseCharacter>(SourceController->GetPawn());
	// 		}
	// 		else
	// 		{
	// 			SourceCharacter = Cast<ABaseCharacter>(SourceActor);
	// 		}
	//
	// 		// Set the causer actor based on context if it's set
	// 		if (Context.GetEffectCauser())
	// 		{
	// 			SourceActor = Context.GetEffectCauser();
	// 		}
	// 	}
	//
	// 	// Try to extract a hit result
	// 	FHitResult HitResult;
	// 	if (Context.GetHitResult())
	// 	{
	// 		HitResult = *Context.GetHitResult();
	// 	}
	//
	// 	// Store a local copy of the amount of damage done and clear the damage attribute
	// 	const float LocalDamageDone = GetDamage();
	// 	SetDamage(0.f);
	//
	// 	if (LocalDamageDone > 0)
	// 	{
	// 		// Apply the health change and then clamp it
	// 		const float OldHealth = GetHealth();
	// 		SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));
	//
	// 		if (TargetCharacter)
	// 		{
	// 			// This is proper damage
	// 			TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);
	//
	// 			// Call for all health changes
	// 			TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
	// 		}
	// 	}
	// }
	// else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	// {
	// 	// Handle other health changes such as from healing or direct modifiers
	// 	// First clamp it
	// 	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	//
	// 	if (TargetCharacter)
	// 	{
	// 		// Call for all health changes
	// 		TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
	// 	}
	// }
	// else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	// {
	// 	// Clamp mana
	// 	SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	//
	// 	if (TargetCharacter)
	// 	{
	// 		// Call for all mana changes
	// 		TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
	// 	}
	// }
	// else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	// {
	// 	if (TargetCharacter)
	// 	{
	// 		// Call for all movespeed changes
	// 		TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
	// 	}
	// }
}

void UCharacterAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue,NewMaxValue) && AbilityComp)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f)? (CurrentValue * NewMaxValue/CurrentMaxValue) - CurrentValue : NewMaxValue;
		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive,NewDelta);
	}
}