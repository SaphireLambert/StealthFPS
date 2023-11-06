// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "StealthPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemySoldier::AEnemySoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup for the body mesh
	bodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy Character Mesh"));
	bodyMesh->SetupAttachment(GetCapsuleComponent());
	bodyMesh->AddRelativeRotation(FRotator(0, 0, -90));
	bodyMesh->AddRelativeLocation(FVector(0, 0, 0));

	//Setup for the gun mesh
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	gunMesh->SetOnlyOwnerSee(false);
	gunMesh->bCastDynamicShadow = true;
	gunMesh->CastShadow = true;

	//Setup for the gun muzzle
	muzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	muzzleLocation->SetupAttachment(gunMesh);
	muzzleLocation->SetRelativeLocation(FVector(0.2f, 22, 9.4f));
}

// Called when the game starts or when spawned
void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();

	gunMesh->AttachToComponent(bodyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ShotGunSocket"));
}

// Called every frame
void AEnemySoldier::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

UBehaviorTree* AEnemySoldier::GetBehaviorTree() const
{
	return Tree;
}


float AEnemySoldier::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	if (Health <= 0)
	{
		return 0;
	}

	float DamageCaused = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);
	DamageCaused = FMath::Min(Health, DamageCaused);

	Health -= DamageCaused;

	if (Health <= 0)
	{
		EnemyDied();
	}

	return damageAmount;
}

void AEnemySoldier::ShootShotGun()
{
	FHitResult hit;

	const float weaponRange = 750;
	const FVector startTrace = muzzleLocation->GetComponentLocation();
	const FVector forwardVector = muzzleLocation->GetForwardVector();
	const FVector endTrace = (forwardVector * weaponRange) + startTrace;

	FCollisionQueryParams queryparameters;
	queryparameters.AddIgnoredActor(this);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OUT hit, startTrace, endTrace, ECC_GameTraceChannel1, queryparameters);


	if (isHit)
	{
		FPointDamageEvent damageEvent(33, hit, forwardVector, nullptr); //Calls the damage event to deal damage to whatever the gun hit
		hit.GetActor()->TakeDamage(33, damageEvent, GetInstigatorController(), this);//Damages the actor that the raycast hit
		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Red, true, -1, 0, 1);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit Player"));

	}
}

void AEnemySoldier::EnemyDied()
{
	bodyMesh->SetSimulatePhysics(true);//Creates the ragdoll effect

	DetachFromControllerPendingDestroy();//Detaches the enemy AI controller to that its no longer active afer the enemy is dead. 

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Deactivates the collision for the enemy so players dont randomly get stick on invisible capsule
}





