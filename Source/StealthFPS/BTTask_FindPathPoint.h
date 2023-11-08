// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPathPoint.generated.h"

UCLASS()
class STEALTHFPS_API UBTTask_FindPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	explicit UBTTask_FindPathPoint(FObjectInitializer const& objectInializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

private:

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector patrolPathVectorKey;
};
