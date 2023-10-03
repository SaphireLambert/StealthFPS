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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Finn Has Edited \/

public: 
	//Created the skeletal Mesh Component for the player character in the editor
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* bodyMesh;

	//Created the gun skeletal mesh in the editor
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* gunMesh;

	//Creates location for the muzzle location
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* muzzleLocation;

	//Creates first person camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class UCameraComponent* firstPersonCamera;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* interactableDetection;

	//The turn rate for the camera look variable Horizontal
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		float turnVerticalRate;

	//The turn rate for the camera look variable Vertical
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		float turnHorizontalRate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector gunOffset;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterAttributes)
	float playerHealth = 100; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterAttributes)
	float playerDamage = 100;

	UFUNCTION()
	void InteractWithObject(UPrimitiveComponent* interactComp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 otherBodyIndex,
		bool bFromSweep, const FHitResult& interact);
	
	virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent, class AController* eventInstigator, AActor* damageCauser);

protected:

	void FireGun();

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);

	void VerticalTurnAtRate(float rate);
	void HorizontalTurnAtRate(float rate);

	//void Crouch();
	//void StopCrouch();
private:
	//class UAIPerceptionStimiliSourceComponent* StimulusSource;
	void SetupStimuliSource();

	void ExitGame();
};
