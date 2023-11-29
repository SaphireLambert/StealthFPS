// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ShootAtPlayer.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "EnemyAI_Controller.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnemySoldier.h"
#include "TimerManager.h"

UMyBTTask_ShootAtPlayer::UMyBTTask_ShootAtPlayer(FObjectInitializer const& objectInitializer) :
	UBTTask_BlackboardBase{objectInitializer}
{
	NodeName = TEXT("Shoot the Player");
}

EBTNodeResult::Type UMyBTTask_ShootAtPlayer::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	if (auto* const cont = Cast<AEnemyAI_Controller>(ownerComp.GetAIOwner()))
	{
		if (auto* npc = Cast<AEnemySoldier>(cont->GetCharacter()))
		{
			if (npc)
			{
				npc->ShootShotGun();
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
