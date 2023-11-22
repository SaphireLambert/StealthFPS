// Fill out your copyright notice in the Description page of Project Settings.

//GAME
#include "EnemySoldier.h"
#include "StealthPlayerCharacter.h"
#include "EnemyAI_Controller.h"

//ENGINE
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

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

	ShotGunMuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Muzzle Flash"));
	ShotGunMuzzleFlash->SetupAttachment(muzzleLocation);
	ShotGunMuzzleFlash->SetAutoActivate(false);
	
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

AEnemyPatrolPath* AEnemySoldier::GetPatrolPath() const
{
	return patrolPath;
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

void AEnemySoldier::Fire()
{
	gunMesh->PlayAnimation(fireingGun, false);

	FHitResult hit;

	const float weaponRange = 400.0f;
	const FVector startTrace = muzzleLocation->GetComponentLocation();
	const FVector forwardVector = muzzleLocation->GetForwardVector();
	const FVector endTrace = (forwardVector * weaponRange) + startTrace;

	FCollisionQueryParams queryparameters;

	bool isHit = UKismetSystemLibrary::SphereTraceSingle(this, startTrace, endTrace, 40.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, TArray<AActor*>(), EDrawDebugTrace::ForDuration, hit, true);

	if (isHit)
	{
		FPointDamageEvent damageEvent(33, hit, forwardVector, nullptr); //Calls the damage event to deal damage to whatever the gun hit
		hit.GetActor()->TakeDamage(33, damageEvent, GetInstigatorController(), this);//Damages the actor that the raycast hit
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RayCast Hit Actor"));
	}
}

void AEnemySoldier::ShootShotGun()
{
	GetWorldTimerManager().SetTimer(DelayedFunctionHandle, this, &AEnemySoldier::Fire, 0.5, true); //Adds a delay for the firing function
}

void AEnemySoldier::EnemyDied()
{
	Destroy();

	bodyMesh->SetSimulatePhysics(true);//Creates the ragdoll effect

	DetachFromControllerPendingDestroy();//Detaches the enemy AI controller to that its no longer active afer the enemy is dead. 

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Deactivates the collision for the enemy so players dont randomly get stick on invisible capsule
}





