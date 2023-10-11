// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI_Controller.h"
#include "EnemySoldier.h"
#include "StealthPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
AEnemyAI_Controller::AEnemyAI_Controller(FObjectInitializer const& onjectInitializer)
{
	SetupPerceptionSystem();
}

void AEnemyAI_Controller::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	if (AEnemySoldier* const enemynpc = Cast<AEnemySoldier>(inPawn))
	{
		if (UBehaviorTree* const behTree = enemynpc->GetBehaviorTree()) 
		{
			UBlackboardComponent* b;
			UseBlackboard(behTree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(behTree);
		}
	}
}

void AEnemyAI_Controller::SetupPerceptionSystem()
{
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));

	if (sightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		sightConfig->SightRadius = 1000;
		sightConfig->LoseSightRadius = sightConfig->SightRadius + 100;
		sightConfig->PeripheralVisionAngleDegrees = 90;
		sightConfig->SetMaxAge(5);
		sightConfig->AutoSuccessRangeFromLastSeenLocation = 520;
		sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAI_Controller::OnTargetDectected);
		GetPerceptionComponent()->ConfigureSense(*sightConfig);

	}
}

void AEnemyAI_Controller::OnTargetDectected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto* const ch = Cast<AStealthPlayerCharacter>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", stimulus.WasSuccessfullySensed());
	}
}

