// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPatrolPath.h"

// Sets default values
AEnemyPatrolPath::AEnemyPatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AEnemyPatrolPath::GetPatrolPoint(int const index) const
{
	return patrolPoints[index];
}

int AEnemyPatrolPath::Num() const
{
	return patrolPoints.Num();
}

