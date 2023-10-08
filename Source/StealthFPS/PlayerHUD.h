// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"


/**
 * 
 */

UCLASS(Abstract)
class STEALTHFPS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	//Update HUD with current player health
	void SetHealth(float currentHealth, float maxHealth);

	//Accesses the widget to display the current player health
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* healthBar;
};
