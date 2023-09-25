// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySoldier.generated.h"

UCLASS()
class STEALTHFPS_API AEnemySoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemySoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
//Finn Edit From Here\/
public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DamageCollision;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, 
		UPrimitiveComponent* otherComp, int32 otherBodyIndex, 
		bool bFromSweep, const FHitResult& hit);

	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
	class UAISenseConfig_Sight* sightConfuguartion;

	UFUNCTION()
	void OnSensed(const TArray<AActor*>& updatedActors);

	UPROPERTY(VisibleAnywhere, Category = Movement)
	FRotator enemyRotation;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	FVector baseLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector curentVelocity;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	float movementSpeed;

	void SetNewRotation(FVector targetPosition, FVector currentPosition);

	bool backToBaseLocation;

	FVector newLocation;

	float distanceSquared;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxhealth = 100;

	UPROPERTY(EditAnywhere)
	float damageValue = 5;

public:
	void DealDamage(float damageAmount);
};
