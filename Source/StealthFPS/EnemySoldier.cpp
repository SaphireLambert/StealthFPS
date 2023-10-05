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

	//Finn Edited \/
	killBox = CreateDefaultSubobject<UBoxComponent>(TEXT("killBox"));
	killBox->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	killBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemySoldier::CauseDamageToPlayer);
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

void AEnemySoldier::CauseDamageToPlayer(UPrimitiveComponent* interactComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& interact)
{
	if (auto playerCharacter = Cast<AStealthPlayerCharacter>(otherActor))
	{
		playerCharacter->TakeDamage(100, FDamageEvent(), GetInstigatorController(), this);
	}
	
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
		UE_LOG(LogTemp, Warning, TEXT("Enemy has Died"));
		//DisableInput(GetWorld()->EnemyAI_Controller());
		GetMesh()->SetSimulatePhysics(true);
	}

	return damageAmount;
}





