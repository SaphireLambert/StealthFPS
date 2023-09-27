// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObjective.h"

// Sets default values
ALevelObjective::ALevelObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	overlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = overlapComponent;

}

void ALevelObjective::BeginPlay()
{

}

void ALevelObjective::Tick(float DeltaTime)
{

}



