// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerCharacterHUD.generated.h"

struct FInteractableData;
class UMainMenuUserWidget;
class UInteractionWidget;

UCLASS()
class STEALTHFPS_API APlayerCharacterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//==================================================================
	// PROPERIES AND VARIABLES
	//==================================================================

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenuUserWidget> mainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> interactionWidgetClass;

	bool bIsMenuVisible;

	//==================================================================
	// FUNCTIONS
	//==================================================================

	APlayerCharacterHUD();

	void DisplayMenu();
	void HideMenu();

	void ShowInteractionWidget();
	void HideInteractionWidget();

	void UpdateInteractionWidget(const FInteractableData* InteractableData);

protected:
	//==================================================================	
	// PROPERIES AND VARIABLES	
	//==================================================================
	UPROPERTY()
	UMainMenuUserWidget* mainMenuWidget;

	UPROPERTY()
	UInteractionWidget* interactionWidget;

	//==================================================================
	// FUNCTIONS
	//==================================================================

	virtual void BeginPlay()override;

};
