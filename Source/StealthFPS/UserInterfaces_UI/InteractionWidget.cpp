#include "InteractionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
//#include "Interfaces/InteractInterface.h"


// Fill out your copyright notice in the Description page of Project Settings.

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData)
{
	/*switch (InteractableData->interactableType) 
	{
	case EInteractableType::Pickup: break;
	}*/
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
