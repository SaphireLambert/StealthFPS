// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"
#include "EnemyAI_Controller.h"
#include "EnemySoldier.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "string.h"

#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "Containers/UnrealString.h"

// Function to convert a double to a string
FString DoubleToString(double Value)
{
	// Convert the double to an FString
	FString StringValue = FString::SanitizeFloat(Value);

	// Return the converted FString
	return StringValue;
}

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

			//Test to see if the code makes it into this if statement ___ Results show success
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Able to cast to blackboard"));

			// Cast to AEnemySoldier
			if (auto* npc = Cast<AEnemySoldier>(cont->GetPawn())) //Code wont cast to the enemy soldier class
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entered the if statement"));
				auto const pathPoint = npc->GetPatrolPath()->GetPatrolPoint(index);

				// Debug line to find the position of pathPoint
				FString targetPosString = pathPoint.ToString();
				UE_LOG(LogTemp, Warning, TEXT("Vector as a string: %s"), *targetPosString);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Path point pos"));

				auto const globalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(pathPoint);
				bc->SetValueAsVector(patrolPathVectorKey.SelectedKeyName, globalPoint);

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("JUst before success"));
				// Finish with success
				FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
