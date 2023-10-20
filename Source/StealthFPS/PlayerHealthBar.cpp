#include "PlayerHealthBar.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHealthBar.h"
#include "StealthPlayerCharacter.h"
#include "Components/ProgressBar.h"

//UPlayerHealthBar::UPlayerHealthBar()
//{
//    //UProgressBar* playerHealthBar = NewObject<UProgressBar>(this, UProgressBar::StaticClass());
//}

void UPlayerHealthBar::UpdateHealthPercent()
{
    playerReference->playerMaxHealth = maxHealth;
    playerReference->playerCurrentHealth = currentHealth;

    playerHealthBar->SetPercent(currentHealth/maxHealth);  
}
