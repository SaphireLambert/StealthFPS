// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncrimentPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API UBTTask_IncrimentPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	explicit UBTTask_IncrimentPathIndex(FObjectInitializer const& objectInializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

private:

	enum class EDirectionType{forward, reverse};

	EDirectionType direction = EDirectionType::forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bBiDirectional = false;
};
