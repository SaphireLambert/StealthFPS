#include "InteractionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
//#include "Interfaces/InteractInterface.h" //Cant find for some reason


// Fill out your copyright notice in the Description page of Project Settings.

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
	//switch (InteractableData->interactableType) 
	//{
	//case EInteractableType::Pickup: 
	//	keyPressText->SetText(FText::FromString("Press"));
	//	InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed)

	//	if (InteractableData < 2)
	//	{
	//		quantity->SetVisibility(ESlateVisibility::Collapsed)
	//	}
	//	else
	//	{
	//		quantity->SetText(FText::Format(NSLOCTEXT("InteractionWIdget", "quantity", "X{0}"),
	//			InteractableData->quantity));
	//		quantity_SetVisibility(ESlateVisibility::Visible);
	//	}

	//	break;

	//case EInteractableType::NonPlayerCharacter: break;

	//case EInteractableType::Entry: break;

	//case EInteractableType::Device: break;

	//case EInteractableType::Toggle: break;

	//case EInteractableType::Container: break;
	//}

	//actionText->SetText(FText::FromString(InteractableData->action));
	//nameText->SetText(InteractableData->Name);
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
