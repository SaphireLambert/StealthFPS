// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StealthPlayerCharacter.generated.h"

UCLASS()
class STEALTHFPS_API AStealthPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStealthPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;\

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* bodyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* gunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* muzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class UCameraComponent* firstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		float turnVerticalRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		float turnHorizontalRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector gunOffset;

protected:

	void FireGun();

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void VerticalTurnAtRate(float rate);
	void HorizontalTurnAtRate(float rate);

};
