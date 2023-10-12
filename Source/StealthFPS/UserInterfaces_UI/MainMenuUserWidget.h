// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StealthFPS/StealthPlayerCharacter.h"
#include "MainMenuUserWidget.generated.h"


UCLASS()
class STEALTHFPS_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AStealthPlayerCharacter* playerCharacter;

protected:

	virtual void NativeOnInitialized()override;
	virtual void NativeConstruct()override;


	
};
