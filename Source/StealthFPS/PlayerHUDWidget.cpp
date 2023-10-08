// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "Components/ProgressBar.h"
#include "StealthPlayerCharacter.h"

void UPlayerHUDWidget::SetHealth(float currentHealth, float maxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(currentHealth / maxHealth);
	}
}
