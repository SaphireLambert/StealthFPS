// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthBar.generated.h"

class AStealthPlayerCharacter;
class UProgressBar;
/**
 * 
 */
UCLASS()
class STEALTHFPS_API UPlayerHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	float currentHealth;

	UPROPERTY()
	float maxHealth;


	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
	AStealthPlayerCharacter* playerReference;

	void UpdateHealthPercent();


	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Player Health Bar | Player Reference")
	UProgressBar* playerHealthBar;
	
};
