#include "PlayerHealthBar.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHealthBar.h"
#include "Components/ProgressBar.h"

void UPlayerHealthBar::UpdateHealthPercent(float max, float current)
{
    playerHealthBar->SetPercent(current/max);  
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Updating health Percent bar"));
}
