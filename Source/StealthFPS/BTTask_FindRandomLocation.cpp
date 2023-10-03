// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "EnemyAI_Controller.h"
#include "NavigationSystem.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location in NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the AI and the enemy NPC
	if (auto* const cont = Cast<AEnemyAI_Controller>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = cont->GetPawn())
		{
			//Obtains the original location opf the NPC
			auto const origin = npc->GetActorLocation();

			//Gets the navigation system and generates a random location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld())) 
			{
				FNavLocation location;
				if (NavSys->GetRandomPointInNavigableRadius(origin, searchRadius, location))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), location.Location);
				}

				//Finished the algorithim with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
