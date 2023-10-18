// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuClass.generated.h"

UCLASS()
class STEALTHFPS_API AMainMenuClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMenuClass();	

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UUserWidget* MainMenuWidgetInstance;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
};
