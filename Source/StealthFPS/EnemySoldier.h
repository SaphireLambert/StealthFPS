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
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//Finn Edit From Here\/
public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* DamageCollision;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, 
		UPrimitiveComponent* otherComp, int32 otherBodyIndex, 
		bool bFromSweep, const FHitResult& hit);


};
