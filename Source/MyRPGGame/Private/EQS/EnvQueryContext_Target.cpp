// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryContext_Target.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Characters/PlayerCharacter.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"

void UEnvQueryContext_Target::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UObject* QuerierObject = QueryInstance.Owner.Get();
	if ((QuerierObject == nullptr))
	{
		return;
	}
	AActor* QuerierActor = Cast<AActor>(QuerierObject);
	AActor* ResultingActor = NULL;
	if (!QuerierActor)
	{
		return;
	}
	if (AAIController* Controller = UAIBlueprintHelperLibrary::GetAIController(QuerierActor))//空指针判定可能找不到目标
	{
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(SelectKeyName)))
        {
        	ResultingActor = PlayerCharacter;
        }
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
	
	//内容写在这里
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ResultingActor);
}

UEnvQueryContext_Target::UEnvQueryContext_Target()
{
	SelectKeyName = UKismetSystemLibrary::MakeLiteralName(TEXT("EnemyActor"));
}
