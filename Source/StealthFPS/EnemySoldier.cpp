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

	damageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	damageCollision->SetupAttachment(RootComponent);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	sightConfuguartion = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));

	sightConfuguartion->SightRadius = 1250;
	sightConfuguartion->LoseSightRadius = 1280;
	sightConfuguartion->PeripheralVisionAngleDegrees = 90;
	sightConfuguartion->DetectionByAffiliation.bDetectEnemies = true;
	sightConfuguartion->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfuguartion->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfuguartion->SetMaxAge(0.1f);

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
	
	damageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemySoldier::OnHit);

	baseLocation = this->GetActorLocation();
}

// Called every frame
void AEnemySoldier::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (!curentVelocity.IsZero())
	{
		newLocation = GetActorLocation() + curentVelocity * deltaTime;

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

void AEnemySoldier::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, 
UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& hit)
{

	AStealthPlayerCharacter* Char = Cast<AStealthPlayerCharacter>(otherActor);

	if (Char)
	{
		Char->DealDamage(damageValue);
		UE_LOG(LogTemp, Warning, TEXT("Player Got HIT"));
	}

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
	enemyHealth -= damageAmount;

	if (enemyHealth <= 0)
	{
		Destroy();
	}
}

