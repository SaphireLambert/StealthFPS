// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerCharacterHUD.generated.h"

struct FInteractableData;
class UInteractionWidget;
class UReloadAmmoCounter;
class UPlayerHealthBar;
class UCrossHair;

UCLASS()
class STEALTHFPS_API APlayerCharacterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//==================================================================
	// PROPERIES AND VARIABLES
	//==================================================================

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> interactionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPlayerHealthBar> playerHealthClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UCrossHair> crossHairClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UReloadAmmoCounter> ammoCounterClass;

	UPROPERTY()
	UPlayerHealthBar* playerHealthWidget;

	UPROPERTY()
	UReloadAmmoCounter* ammoCountWidget;
	UPROPERTY()
	UInteractionWidget* interactionWidget;

	UPROPERTY()
	UCrossHair* crossHairWidget;

	//==================================================================
	// FUNCTIONS
	//==================================================================

	APlayerCharacterHUD();


	void ShowInteractionWidget();
	void HideInteractionWidget();

	void UpdateInteractionWidget(const FInteractableData* InteractableData);

	
protected:
	//==================================================================	
	// PROPERIES AND VARIABLES	
	//==================================================================

	//==================================================================
	// FUNCTIONS
	//==================================================================

	virtual void BeginPlay()override;

};
