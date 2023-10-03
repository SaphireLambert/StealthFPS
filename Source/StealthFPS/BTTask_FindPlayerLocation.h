// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API UBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_FindPlayerLocation(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
private:

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	bool searchRandom = false;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float searchRadius = 150;
};
