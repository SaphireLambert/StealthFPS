#include "MainMenuUserWidget.h"
// Fill out your copyright notice in the Description page of Project Settings.

void UMainMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	playerCharacter = Cast<AStealthPlayerCharacter>(GetOwningPlayerPawn());
}
