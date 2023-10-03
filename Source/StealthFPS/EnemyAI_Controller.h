// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHFPS_API AEnemyAI_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	explicit AEnemyAI_Controller(FObjectInitializer const& objectInitializer);

protected:

	virtual void OnPossess(APawn* inPawn) override;
private:
	class UAISenseConfig_Sight* sightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDectected(AActor* actor, FAIStimulus const stimulus);
};
