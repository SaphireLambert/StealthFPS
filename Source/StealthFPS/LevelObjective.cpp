// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObjective.h"
#include "StealthPlayerCharacter.h"

// Sets default values
ALevelObjective::ALevelObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	visualComponent = CreateDefaultSubobject<UMeshComponent>(TEXT("Visual Mesh Component"));

	overlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	overlapComponent->SetupAttachment(RootComponent);

}

void ALevelObjective::BeginPlay()
{
	overlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelObjective::onOverLap);
}

void ALevelObjective::Tick(float DeltaTime)
{

}

void ALevelObjective::onOverLap(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& hit)
{
	AStealthPlayerCharacter* Char = Cast<AStealthPlayerCharacter>(otherActor);
	if (Char)
	{
		FGenericPlatformMisc::RequestExit(true);
	}
}



