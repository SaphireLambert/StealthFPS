#include "InteractionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractInterface.h"


// Fill out your copyright notice in the Description page of Project Settings.

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData)
{
	switch (InteractableData->interactableType) 
	{
	case EInteractableType::Pickup: 
		keyPressText->SetText(FText::FromString("Press"));
		interactionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		if (InteractableData->quantity < 2)
		{
			quantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			quantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "quantityText", "X{0}"),
				InteractableData->quantity));
			quantityText->SetVisibility(ESlateVisibility::Visible);
		}

		actionText->SetText(InteractableData->action);
		nameText->SetText(InteractableData->name);

	break;

	case EInteractableType::NonPlayerCharacter: break;

	case EInteractableType::Entry: break;

	case EInteractableType::Device: 
		keyPressText->SetText(FText::FromString("Press"));
		interactionProgressBar->SetVisibility(ESlateVisibility::Visible);
		quantityText->SetVisibility(ESlateVisibility::Collapsed);
		actionText->SetText(InteractableData->action);
		nameText->SetText(InteractableData->name);
		break;

	case EInteractableType::Toggle: break;

	case EInteractableType::Container: break;
	}
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.0f;
}

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	interactionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	keyPressText->SetText(FText::FromString("Press"));
	currentInteractionDurration = 0.0f;
}
