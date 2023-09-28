// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "LevelObjective.generated.h"

UCLASS()
class STEALTHFPS_API ALevelObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Finn Edited \/
public:
	UFUNCTION()
	void onOverLap(UPrimitiveComponent* hitComp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 otherBodyIndex,
		bool bFromSweep, const FHitResult& hit);

private:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* overlapComponent;

	UPROPERTY(EditAnywhere)
	class UMeshComponent* visualComponent;


};
