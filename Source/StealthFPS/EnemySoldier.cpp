// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"
#include "Components/BoxComponent.h"
#include "StealthPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/DamageEvents.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AEnemySoldier::AEnemySoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Finn EDited \/

	//damageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	//damageCollision->SetupAttachment(RootComponent);

	//AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	//sightConfuguartion = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));

	//sightConfuguartion->SightRadius = 1000;
	//sightConfuguartion->LoseSightRadius = 1055;
	//sightConfuguartion->PeripheralVisionAngleDegrees = 60;
	//sightConfuguartion->DetectionByAffiliation.bDetectEnemies = true;
	//sightConfuguartion->DetectionByAffiliation.bDetectFriendlies = true;
	//sightConfuguartion->DetectionByAffiliation.bDetectNeutrals = true;
	//sightConfuguartion->SetMaxAge(0.1f);

	//AIPerceptionComponent->ConfigureSense(*sightConfuguartion);
	//AIPerceptionComponent->SetDominantSense(sightConfuguartion->GetSenseImplementation());
	//AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemySoldier::OnSensed);


	//curentVelocity = FVector::ZeroVector;
	//movementSpeed = 375;

	//distanceSquared = BIG_NUMBER;


}

// Called when the game starts or when spawned
void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	
	damageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemySoldier::OnHit);

	//baseLocation = this->GetActorLocation();
}

// Called every frame
void AEnemySoldier::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//if (!curentVelocity.IsZero())
	//{
	//	newLocation = GetActorLocation() + curentVelocity * deltaTime;

	//	if (backToBaseLocation)
	//	{

	//		if ((newLocation - baseLocation).SizeSquared2D() < distanceSquared) 
	//		{

	//			distanceSquared = (newLocation - baseLocation).SizeSquared2D();

	//		}
	//		else
	//		{
	//			curentVelocity = FVector::ZeroVector;
	//			distanceSquared = BIG_NUMBER;
	//			backToBaseLocation = false;

	//			SetNewRotation(GetActorForwardVector(), GetActorLocation());
	//		}
	//	}
	//	SetActorLocation(newLocation);
	//}

}


UBehaviorTree* AEnemySoldier::GetBehaviorTree() const
{
	return enemyBehaviourTree;
}

void AEnemySoldier::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor,
UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& hit)
{


}


float AEnemySoldier::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	float damageCaused = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);
	damageCaused = FMath::Min(enemyHealth, damageCaused);

	enemyHealth -= damageCaused;
	if (enemyHealth <= 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Died"));
		Destroy();
	}


	return damageCaused;
}



