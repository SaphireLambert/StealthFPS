// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "InteractionTestActor.generated.h"

UCLASS()
class STEALTHFPS_API AInteractionTestActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionTestActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "TestActor")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditInstanceOnly, Category = "TestActor")
	FInteractableData instanceInteractableData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(AStealthPlayerCharacter* playerCharacter) override;

	

};
