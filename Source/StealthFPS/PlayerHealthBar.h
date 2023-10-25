// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class STEALTHFPS_API UPlayerHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Player Health Bar | Player Reference")
	UProgressBar* playerHealthBar;

	void UpdateHealthPercent(float max, float current);


	
};
