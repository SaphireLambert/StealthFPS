// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHealthBar.h"
#include "StealthPlayerCharacter.h"
#include "Components/ProgressBar.h"

void UPlayerHealthBar::UpdateHealthPercent()
{
    playerReference->playerMaxHealth = maxHealth;
    playerReference->playerCurrentHealth = currentHealth;

    playerHealthBar->SetPercent(currentHealth/maxHealth);  
}
