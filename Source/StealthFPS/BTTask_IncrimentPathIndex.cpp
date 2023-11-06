// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrimentPathIndex.h"
#include "EnemyAI_Controller.h"
#include "EnemySoldier.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrimentPathIndex::UBTTask_IncrimentPathIndex(FObjectInitializer const& objectInializer) : 
	UBTTask_BlackboardBase{ objectInializer }
{
	NodeName = TEXT("Incriment Path Index");
}

EBTNodeResult::Type UBTTask_IncrimentPathIndex::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	//Try to get the AI controller
	if (auto* const cont = Cast<AEnemyAI_Controller>(ownerComp.GetAIOwner()))
	{
		//try and get the enemy NPC
		if (auto* const npc = Cast<AEnemySoldier>(cont->GetPawn()))
		{
			if (auto* const BC = ownerComp.GetBlackboardComponent())
			{
				// Get number of patrol points and min and mix indices
				auto const noOfPoints = npc->GetPatrolPath()->Num();
				auto const minIndex = 0;
				auto const maxIndex = noOfPoints - 1;
				auto index = BC->GetValueAsInt(GetSelectedBlackboardKey());

				//Change the direcvt9ion if we are the at the first or last index and if we are in BIdirectional mode
				if (bBiDirectional)
				{
					if (index >= maxIndex && direction == EDirectionType::forward)
					{
						direction = EDirectionType::reverse;
					}
					else if (index == minIndex && direction == EDirectionType::reverse)
					{
						direction = EDirectionType::forward;
					}
				}
				//Write new balue of index to the blackboard
				BC->SetValueAsInt(GetSelectedBlackboardKey(), (direction == EDirectionType::forward ? ++index : --index) % noOfPoints);

				//Finsih with success
				FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
