// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI_Controller.h"
#include "EnemySoldier.h"

AEnemyAI_Controller::AEnemyAI_Controller(FObjectInitializer const& onjectInitializer)
{
}

void AEnemyAI_Controller::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	/*if (AEnemySoldier* const enemynpc = Cast<AEnemySoldier>(inPawn));
	{
		if (UBehaviorTree* const behTree = enemynpc->GetBehaviorTree()) 
		{
			UBlackboardComponent* blackBoard;
			UseBlackboard(behTree->BlackBoardAsset, [&]blackBoard);
			Blackboard = blackBoard;
			RunBehaviorTree(behTree);
		}
	}*/
}
