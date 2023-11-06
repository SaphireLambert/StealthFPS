// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"
#include "EnemyAI_Controller.h"
#include "EnemySoldier.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& objectInializer) :
	UBTTask_BlackboardBase{objectInializer}
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	//Attempt to find the enemy npc controller
	if (auto* const cont = Cast<AEnemyAI_Controller>(ownerComp.GetAIOwner()))
	{
		// Attempt to get the blackboard component from the behavior tree
		if (auto* const bc = ownerComp.GetBlackboardComponent())
		{
			// Get the current patrol path index from the blackboard 
			auto const index = bc->GetValueAsInt(GetSelectedBlackboardKey());

			//Get the Enemy NPC
			if (auto* npc = Cast<AEnemySoldier>(cont->GetPawn()))
			{
				// Get the current patrol path vector from the enemy NPC - this is local to the patrol path actor
				auto const pathPoint = npc->GetPatrolPath()->GetPatrolPoint(index);

				// convert the local vector to a global point
				auto const globalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(pathPoint);
				bc->SetValueAsVector(patrolPathVectorKey.SelectedKeyName, globalPoint);

				//finish with successs
				FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
