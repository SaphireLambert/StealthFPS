// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"


struct FInteractableData;
class AStealthPlayerCharacter;
class UTextBlock;
class UProgressBar;
UCLASS()
class STEALTHFPS_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
	AStealthPlayerCharacter* playerReference;

	void UpdateWidget(const FInteractableData* InteractableData);

protected:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Reference")
	UTextBlock* nameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Reference")
	UTextBlock* actionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Reference")
	UTextBlock* quantity;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Reference")
	UTextBlock* keyPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Reference")
	UProgressBar* interactionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Player Reference")
	float currentInteractionDurration;

	UFUNCTION(Category = "Interaction Widget | Player Reference")
	float UpdateInteractionProgress();

	virtual void NativeOnInitialized()override;
	virtual void NativeConstruct()override;
};
