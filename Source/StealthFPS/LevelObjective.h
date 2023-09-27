// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelObjective.generated.h"
#include <Components/BoxComponent.h>

UCLASS()
class STEALTHFPS_API ALevelObjective : public AActor
{
	
	
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

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UBoxComponent* overlapComponent;


};
