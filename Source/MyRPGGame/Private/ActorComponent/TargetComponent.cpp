// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/TargetComponent.h"

#include "Characters/EnemyCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	TraceDistance = 5000.f;
	TraceRadius = 5000.f;
	TargetOffset = 0.f;
	LockMoveSpeed = 300.f;
	UnLockMoveSpeed = 500.f;
	CollisionChannel = ECC_Pawn;

	// ...
}


// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!TickKey)
	{
		if (FocusActor)
        	{
        		if (!FocusActor->bIsAlive)
        		{
        			CancelTarget();
        			return;
        		}
        		if ((FocusActor->GetActorLocation()-GetOwner()->GetActorLocation()).Size()>1000.f)
        		{
        			CancelTarget();
        			return;
        		}
        		ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwner());
                
        		if (Character)
        		{
        			if (!Character->bIsAlive)
                    {
                        CancelTarget();
                    	return;
                    }
        			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(),FocusActor->GetActorLocation()+TargetOffset);
        			TargetRotation.Roll = 0.f;
        
        			FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(Character->GetControlRotation(),TargetRotation,GetWorld()->GetDeltaSeconds(),200.f);
        			Character->GetController()->SetControlRotation(NewRotation);
        		}
        	}
	}
	
	// ...
}

void UTargetComponent::ChangeRotationMode()
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (Character == nullptr)
	{
		return;
	}
	bUseControllerRotationYaw = Character->bUseControllerRotationYaw;
	bOrientRotationToMovement = Character->GetCharacterMovement()->bOrientRotationToMovement;
	bUseControllerDesiredRotation = Character->GetCharacterMovement()->bUseControllerDesiredRotation;


		Character->SetLockOn(true);

	Character->bUseControllerRotationYaw = true;
	Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	Character->GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AController* Controller = Character->GetController();
	if (Controller)
	{
		Controller->SetIgnoreLookInput(true);
	}
	Character->GetCharacterMovement()->MaxWalkSpeed = LockMoveSpeed;
}

void UTargetComponent::RestoreRotationMode()
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	if (Character == nullptr)
	{
		return;
	}
	
	Character->SetLockOn(false);
	Character->bUseControllerRotationYaw = bUseControllerRotationYaw;
	Character->GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovement;
	Character->GetCharacterMovement()->bUseControllerDesiredRotation = bUseControllerDesiredRotation;

	AController* Controller = Character->GetController();
	if (Controller)
	{
		Controller->SetIgnoreLookInput(false);
	}
	Character->GetCharacterMovement()->MaxWalkSpeed = UnLockMoveSpeed;
}

void UTargetComponent::Target(AEnemyCharacter* TargetActor)
{
	TargetActor->Select();
	ChangeRotationMode();
	FocusActor = TargetActor;
}

void UTargetComponent::CancelTarget()
{
	RestoreRotationMode();
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(FocusActor);
	if (EnemyCharacter)
	{
		EnemyCharacter->CancelSelect();
	}
	FocusActor = nullptr;
}

void UTargetComponent::FindTarget()
{
	if (FocusActor)
	{
		CancelTarget();
		return;
	}
	FCollisionObjectQueryParams ObjectQueryParams;
	const APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	if (Player == nullptr)
	{
		return;
	}
	const FVector CameraLocation = Player->GetPawnViewLocation();
	const FRotator CameraRotation = Player->GetViewRotation();

	FVector End = CameraLocation + (CameraRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);
	bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits,CameraLocation,End,FQuat::Identity,ObjectQueryParams,Shape);
	FocusActor = nullptr;
	for (auto Hit : Hits)
	{
		AEnemyCharacter* HitActor = Cast<AEnemyCharacter>(Hit.GetActor());
		if (HitActor)
		{
			Target(HitActor);
			break;
		}
	}
}

void UTargetComponent::SetTickKey(bool Out_TickKey)
{
	TickKey = Out_TickKey;
}

