// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterHUD.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Interfaces/InteractInterface.h"
#include "StealthPlayerCharacter.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : currentInteractable(nullptr), lastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
	AActor* currentInteractable;

	UPROPERTY()
	float lastInteractionCheckTime;
};

UCLASS()
class STEALTHFPS_API AStealthPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	//==================================================================
	// PROPERIES AND VARIABLES
	//==================================================================
	

	//Store the players current health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes")
	float playerCurrentHealth; 

	//Store the players maximum health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes")
	float playerMaxHealth = 100;

	//Stores the player damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes")
	float pistolDamage = 100;

	//Bool to see if character is aiming the gun (ADS)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool isAimedIn;

	//Bool to check if the player is crouched or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool isCrouched;
	
	//a float that can be called to deal damage to the player from other classes 
	virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent, 
	class AController* eventInstigator, AActor* damageCauser);

	//==================================================================
	// FUNCTIONS
	//==================================================================

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this character's properties
	AStealthPlayerCharacter();

	//A bool for to see if the character is interacting with an object
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(timerHandle_Interaction); };


protected:

	//==================================================================
	// PROPERIES AND VARIABLES
	//==================================================================

	UPROPERTY()
	APlayerCharacterHUD* HUD;
	
	//Created the skeletal Mesh Component for the player character in the editor
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* bodyMesh;

	//Created the gun skeletal mesh in the editor
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* gunMesh;

	//Creates location for the muzzle location
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USceneComponent* muzzleLocation;

	//Creates first person camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "camera")
		class UCameraComponent* firstPersonCamera;

	//Stores the position of the gunmesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		FVector gunOffset;

	//The turn rate for the camera look variable Horizontal
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "camera")
		float turnVerticalRate;

	//The turn rate for the camera look variable Vertical
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "camera")
		float turnHorizontalRate;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractInterface> targetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	UPlayerHealthBar* playerHealthBar;

	// Ads the AI Stimulai Souce so any AI Character can see the player
	class UAIPerceptionStimuliSourceComponent* stimulusSource;

	float interactioCheckFrequency;

	float interactionCheckDistance;

	FTimerHandle timerHandle_Interaction;

	FInteractionData interactionData;

	//==================================================================
	// FUNCTIONS
	//==================================================================

	//Functions for my interactions
	void PerformInteractionCheck();
	void FoundInteractable(AActor* newInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Shoots the pistol
	void FireGun();

	//Moves the character
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);

	//Turns the character
	void VerticalTurnAtRate(float rate);
	void HorizontalTurnAtRate(float rate);

	//Sets up the stimuli for the AI
	void SetupStimuliSource();

	//Zooms the camera for the ADS function
	void StartZoom();
	void StopZoom();

	//Allows the player to crouch in the game reducing chance to be seen. 
	void StartCrouch();
	void StopCrouch();
};
