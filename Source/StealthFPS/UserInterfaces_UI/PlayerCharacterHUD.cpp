#include "PlayerCharacterHUD.h"
#include "MainMenuUserWidget.h"
#include "InteractionWidget.h"

// Fill out your copyright notice in the Description page of Project Settings.

APlayerCharacterHUD::APlayerCharacterHUD()
{
}

void APlayerCharacterHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (mainMenuClass)
	{
		mainMenuWidget = CreateWidget<UMainMenuUserWidget>(GetWorld(), mainMenuClass);
		mainMenuWidget->AddToViewport(5);
		mainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (interactionWidgetClass)
	{
		interactionWidget = CreateWidget<UInteractionWidget>(GetWorld(), interactionWidgetClass);
		interactionWidget->AddToViewport(1);
		interactionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerCharacterHUD::DisplayMenu()
{
	if (mainMenuWidget)
	{
		bIsMenuVisible = true;
		mainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerCharacterHUD::HideMenu()
{
	if (mainMenuWidget)
	{
		bIsMenuVisible = false;
		mainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerCharacterHUD::ShowInteractionWidget()
{
	if (interactionWidget)
	{
		interactionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerCharacterHUD::HideInteractionWidget()
{
	if (interactionWidget)
	{
		interactionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerCharacterHUD::UpdateInteractionWidget(const FInteractableData* InteractableData)
{
	if (interactionWidget)
	{
		if (interactionWidget->GetVisibility() == ESlateVisibility::Collapsed) 
		{
			interactionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		//interactionWidget->UpdateWidget(InteractableData);
	}
}

