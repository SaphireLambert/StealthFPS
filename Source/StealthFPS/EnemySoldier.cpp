// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"
#include "Components/BoxComponent.h"
#include "StealthPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AEnemySoldier::AEnemySoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Finn EDited \/

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	sightConfuguartion = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));

	sightConfuguartion->SightRadius = 750;
	sightConfuguartion->LoseSightRadius = 1000;
	sightConfuguartion->PeripheralVisionAngleDegrees = 90;
	sightConfuguartion->DetectionByAffiliation.bDetectEnemies = true;
	sightConfuguartion->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfuguartion->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfuguartion->SetMaxAge(0.9f);

	AIPerceptionComponent->ConfigureSense(*sightConfuguartion);
	AIPerceptionComponent->SetDominantSense(sightConfuguartion->GetSenseImplementation());
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemySoldier::OnSensed);


	curentVelocity = FVector::ZeroVector;
	movementSpeed = 375;

	distanceSquared = BIG_NUMBER;


}

// Called when the game starts or when spawned
void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemySoldier::OnHit);

	baseLocation = this->GetActorLocation();
}

// Called every frame
void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!curentVelocity.IsZero())
	{
		newLocation = GetActorLocation() + curentVelocity * DeltaTime;

		if (backToBaseLocation)
		{

			if ((newLocation - baseLocation).SizeSquared2D() < distanceSquared) 
			{

				distanceSquared = (newLocation - baseLocation).SizeSquared2D();

			}
			else
			{
				curentVelocity = FVector::ZeroVector;
				distanceSquared = BIG_NUMBER;
				backToBaseLocation = false;

				SetNewRotation(GetActorForwardVector(), GetActorLocation());
			}
		}
		SetActorLocation(newLocation);
	}

}

// Called to bind functionality to input
void AEnemySoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemySoldier::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, 
UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& hit)
{
}

void AEnemySoldier::OnSensed(const TArray<AActor*>& updatedActors)
{

	for (int i = 0; i < updatedActors.Num(); i++)
	{
		FActorPerceptionBlueprintInfo info;

		AIPerceptionComponent->GetActorsPerception(updatedActors[i], info);

		if (info.LastSensedStimuli[0].WasSuccessfullySensed()) 
		{
			FVector direction = updatedActors[i]->GetActorLocation() - GetActorLocation();
			direction.Z = 0;

			curentVelocity = direction.GetSafeNormal() * movementSpeed;

			SetNewRotation(updatedActors[i]->GetActorLocation(), GetActorLocation());

		}
		else 
		{
			FVector direction = baseLocation - GetActorLocation();
			direction.Z = 0;

			if (direction.SizeSquared2D() > 1)
			{
				curentVelocity = direction.GetSafeNormal() * movementSpeed;

				backToBaseLocation = true;

				SetNewRotation(baseLocation, GetActorLocation());
			}

		}
	}

}

void AEnemySoldier::SetNewRotation(FVector targetPosition, FVector currentPosition)
{

	FVector newDirection = targetPosition - currentPosition;
	newDirection.Z = 0;

	enemyRotation = newDirection.Rotation();

	SetActorRotation(enemyRotation);

}

void AEnemySoldier::DealDamage(float damageAmount)
{
}

