#include "PlayerCharacterHUD.h"
#include "InteractionWidget.h"

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

	/*if (playerHealthClass)
	{
		playerHealthWidget = CreateWidget<UPlayerHealth>(GetWorld(), playerHealthClass);
	}*/
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

