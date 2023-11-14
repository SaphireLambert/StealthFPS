#include "PlayerCharacterHUD.h"
#include "InteractionWidget.h"
#include "PlayerHealthBar.h"
#include "ReloadAmmoCounter.h"
#include "CrossHair.h"

// Fill out your copyright notice in the Description page of Project Settings.

APlayerCharacterHUD::APlayerCharacterHUD()
{
}

void APlayerCharacterHUD::BeginPlay()
{
	Super::BeginPlay();


	if (interactionWidgetClass)
	{
		interactionWidget = CreateWidget<UInteractionWidget>(GetWorld(), interactionWidgetClass);
		interactionWidget->AddToViewport(1);
		interactionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (playerHealthClass)
	{
		playerHealthWidget = CreateWidget<UPlayerHealthBar>(GetWorld(), playerHealthClass);
		playerHealthWidget->AddToViewport(5);
		playerHealthWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (crossHairClass)
	{
		crossHairWidget = CreateWidget<UCrossHair>(GetWorld(), crossHairClass);
		crossHairWidget->AddToViewport(4);
		crossHairWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (ammoCounterClass)
	{
		ammoCountWidget = CreateWidget<UReloadAmmoCounter>(GetWorld(), ammoCounterClass);
		ammoCountWidget->AddToViewport(3);
		ammoCountWidget->SetVisibility(ESlateVisibility::Visible);
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

		interactionWidget->UpdateWidget(InteractableData);
	}
}

