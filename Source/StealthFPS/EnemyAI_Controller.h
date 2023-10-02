// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API AEnemyAI_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	explicit AEnemyAI_Controller(FObjectInitializer const& onjectInitializer);

protected:
	virtual void OnPossess(APawn* inPawn) override;
};
