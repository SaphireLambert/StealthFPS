// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuClass.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainMenuClass::AMainMenuClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuClass::BeginPlay()
{
	Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        MainMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenuWidgetInstance)
        {
            MainMenuWidgetInstance->AddToViewport();
        }
    }
}




void AMainMenuClass::StartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("MainMap"));
}

void AMainMenuClass::QuitGame()
{
}


