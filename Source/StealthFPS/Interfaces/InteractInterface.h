// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

class AStealthPlayerCharacter;

UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"), // Any object the player can pickup (EG: Ammo)
	NonPlayerCharacter UMETA(DisplayName = "NPC"), // Another character the player can interact with
	Entry UMETA(DisplayName = "Entry"), //A door or gate that the player can open/close
	Device UMETA(DisplayName = "TechDevice"), // Some sort of tech device like a computer
	Toggle UMETA(DisplayName = "Toggle"), // A button switch or lever the player can use
	Container UMETA(DisplayName = "Container") // An object that stores different interables inside it (EG: Ammo Box)
};

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

	FInteractableData() :
		interactableType(EInteractableType::Pickup),
		name(FText::GetEmpty()),
		action(FText::GetEmpty()),
		quantity(0),
		interactionDuration(0.0f)
	{

	};

	UPROPERTY(EditInstanceOnly)
	EInteractableType interactableType;

	UPROPERTY(EditInstanceOnly)
	FText name;

	UPROPERTY(EditInstanceOnly)
	FText action;

	//Used only for pickups
	UPROPERTY(EditInstanceOnly)
	int8 quantity;

	UPROPERTY(EditInstanceOnly)
	float interactionDuration;
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STEALTHFPS_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void BeginFocus(); // Begins "focus" animation (Highlight, Pop-up, Whatever)
	virtual void EndFocus(); // Disables/Ends the focus animation

	virtual void BeginInteract(); // Gives the interaction a timer so its not instant 
	virtual void EndInteract();

	virtual void Interact(AStealthPlayerCharacter* playerCharacter); // Allows the player to interact with the object

	FInteractableData interactableData;

};
