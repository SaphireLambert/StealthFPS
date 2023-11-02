// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_ShootAtPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API UMyBTTask_ShootAtPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	explicit UMyBTTask_ShootAtPlayer(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class AEnemySoldier> EnemySoldierClass;

	UPROPERTY()
	AEnemySoldier* enemySoldier;
};
