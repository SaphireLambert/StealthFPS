// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/ProgressBar.h"

void UPlayerHUD::SetHealth(float currentHealth, float maxHealth)
{
	if (healthBar)
	{
		healthBar->SetPercent(currentHealth / maxHealth);
	}
}
