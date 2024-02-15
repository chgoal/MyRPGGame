// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CloseInWeapon.h"

#include "DrawDebugHelpers.h"
#include "Characters/PlayerCharacter.h"
#include "MyRPGGame/MyRPGGame.h"


void ACloseInWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponMsg.Attack = AttackPower;
	InitSocketTransForm();
}

void ACloseInWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACloseInWeapon::TryToAttack()
{
	Super::TryToAttack();
	StartAttack();
}

void ACloseInWeapon::StopAttack()
{
	Super::StopAttack();
	EndAttack();
}

void ACloseInWeapon::TrySettlementAttack(float Damage)
{
	Super::TrySettlementAttack(Damage);
	SettlementAttack(Damage);
}


void ACloseInWeapon::HideWeapon(bool Out_State)
{
	if (MineSkinInterface)
	{
		if (SkeletalMeshComponent->SkeletalMesh)
		{
			SkeletalMeshComponent->SetVisibility(Out_State);
		}
		else if (StaticMeshComponent->GetStaticMesh())
		{
			StaticMeshComponent->SetVisibility(Out_State);
		}
	}
}

void ACloseInWeapon::InitSocketTransForm()
{
	if (SocketNames.Num()!=0)
	{
		if (SkeletalMeshComponent->SkeletalMesh)
		{
			for (auto Name : SocketNames)
			{
				SocketTransform.Add(SkeletalMeshComponent->GetSocketTransform(Name));
			}
		}
		else if (StaticMeshComponent->GetStaticMesh())
		{
			for (auto Name : SocketNames)
			{
				SocketTransform.Add(StaticMeshComponent->GetSocketTransform(Name));
			}
		}
	}
}

bool ACloseInWeapon::TryUpdateTransform()
{
	if (SocketNames.Num() != 0)
	{
		if (SkeletalMeshComponent->SkeletalMesh)
		{
			SocketTransform.Empty();
			for (auto Name : SocketNames)
			{
				SocketTransform.Add(SkeletalMeshComponent->GetSocketTransform(Name));
			}
			return true;
		}
		if (StaticMeshComponent->GetStaticMesh())
		{
			SocketTransform.Empty();
			for (auto Name : SocketNames)
			{
				SocketTransform.Add(StaticMeshComponent->GetSocketTransform(Name));
			}
			return true;
		}
	}
	return false;
}

void ACloseInWeapon::TimeFunction()
{
	if (SkeletalMeshComponent->SkeletalMesh)
	{
		for (int i = 0;i < SocketNames.Num();i++)
		{
			GetWorld()->LineTraceMultiByChannel(HitResults,SocketTransform[i].GetLocation(),SkeletalMeshComponent->GetSocketLocation(SocketNames[i]),ECC_WeaponTrace);
			//DrawDebugLine(GetWorld(),SocketTransform[i].GetLocation(),SkeletalMeshComponent->GetSocketLocation(SocketNames[i]),FColor::Red,false,2.f);
			for (auto Hit : HitResults)
			{
				if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Hit.Actor))
				{
					if (BaseCharacter != Cast<ABaseCharacter>(MineSkinInterface))
					{
						if (!HitActors.Contains(BaseCharacter))
						{
							SavedResults.Add(Hit);
						}//保存首次受击位置状态
						HitActors.AddUnique(BaseCharacter);
					}	
				}
				//加入新的受击对象
			}
		}
	}
	if (StaticMeshComponent->GetStaticMesh())
	{
		for (int i = 0;i<SocketNames.Num();i++)
		{
			GetWorld()->LineTraceMultiByChannel(HitResults,SocketTransform[i].GetLocation(),StaticMeshComponent->GetSocketLocation(SocketNames[i]),ECC_WeaponTrace);
			//DrawDebugLine(GetWorld(),SocketTransform[i].GetLocation(),StaticMeshComponent->GetSocketLocation(SocketNames[i]),FColor::Red,false,4.f);
			for (auto Hit : HitResults)
			{
				if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Hit.Actor))
				{
					if (BaseCharacter != Cast<ABaseCharacter>(MineSkinInterface))
					{
						if (BaseCharacter->GetGenericTeamId() != Cast<ABaseCharacter>(MineSkinInterface)->GetGenericTeamId())
						{
							if (!HitActors.Contains(BaseCharacter))
							{
								SavedResults.Add(Hit);
							}//保存首次受击位置状态
							HitActors.AddUnique(BaseCharacter);
						}
					}
				}
			}
		}
	}
	TryUpdateTransform();
	
}

void ACloseInWeapon::GainDamage(AActor* Actor)
{
	
	if (ABaseCharacter* DamageCharacter = Cast<ABaseCharacter>(Actor))
	{
		FPointDamageEvent DamageEvent;
		DamageCharacter->TakeDamage(1,DamageEvent,Cast<ABaseCharacter>(MineSkinInterface)->GetController(),this);
	}
}
void ACloseInWeapon::StartAttack()
{
	TryUpdateTransform();
	GetWorld()->GetTimerManager().SetTimer(WeaponTimerHandle,this,&ACloseInWeapon::TimeFunction,0.01f,true);
}

void ACloseInWeapon::SettlementAttack(float Damage)
{
	// if (Cast<ABaseCharacter>(MineSkinInterface)->GetHurt())
	// {
	// 	HitActors.Empty();
	// 	SavedResults.Empty();
	// }
	if (MineSkinInterface)
	{
		if (ABaseCharacter* CauseCharacter = Cast<ABaseCharacter>(MineSkinInterface))
		{
			float MyDamage = CauseCharacter->GetFullAttack();
			for (auto Actor : HitActors)
			{
				if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Actor))
				{
					FPointDamageEvent PointDamageEvent;
					for (auto Save : SavedResults)
					{
						if (Cast<ABaseCharacter>(Save.Actor) == BaseCharacter)
						{
							if (BaseCharacter && BaseCharacter->GetController())
							{
								//UE_LOG(LogTemp, Log, TEXT("WeaponMsg=%f"),WeaponMsg.Attack)
								BaseCharacter->GotDamage(MyDamage+AttackPower,PointDamageEvent,CauseCharacter->GetController(),CauseCharacter,Save);
							}
							break;
						}
					}
				
					//UE_LOG(LogTemp, Log, TEXT("HitCharacter = %s"),*BaseCharacter->GetName())
				}
			}
		}
	}
}

void ACloseInWeapon::EndAttack()
{
	HitActors.Empty();
	SavedResults.Empty();
	GetWorld()->GetTimerManager().ClearTimer(WeaponTimerHandle);
	//GetWorld()->GetTimerManager().ClearTimer(WeaponTimerHandle);
	// if (MineSkinInterface)
	// {
	// 	const ABaseCharacter* MineBaseCharacter = Cast<ABaseCharacter>(MineSkinInterface);
	// 	for (auto Actor : HitActors)
	// 	{
	// 		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Actor))
	// 		{
	// 			if (BaseCharacter!=MineBaseCharacter)
	// 			{
	// 				FPointDamageEvent PointDamageEvent;
	// 				BaseCharacter->TakeDamage(10,PointDamageEvent,BaseCharacter->GetController(),BaseCharacter);
	// 			}
	// 		}
	// 	}
	// 	HitActors.Empty();
	// }
}

FTransform ACloseInWeapon::GetSocketTransform(FName SocketName)
{
	FTransform Transform;
	if (SkeletalMeshComponent->SkeletalMesh)
	{
		return SkeletalMeshComponent->GetSocketTransform(SocketName);
	}
	if(StaticMeshComponent->GetStaticMesh())
	{
		return StaticMeshComponent->GetSocketTransform(SocketName);
	}
	return Transform;
	
}
