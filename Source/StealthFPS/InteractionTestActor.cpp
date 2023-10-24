// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTestActor.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AInteractionTestActor::AInteractionTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	SetRootComponent(mesh);
}

// Called when the game starts or when spawned
void AInteractionTestActor::BeginPlay()
{
	Super::BeginPlay();

	interactableData = instanceInteractableData;
}
// Called every frame
void AInteractionTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionTestActor::BeginFocus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Begin Focus"));
	if (mesh)
	{
		mesh->SetRenderCustomDepth(true);
	}
}

void AInteractionTestActor::EndFocus()
{
	if (mesh)
	{
		mesh->SetRenderCustomDepth(false);
	}
}

void AInteractionTestActor::BeginInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Begining Interaction"));
}

void AInteractionTestActor::EndInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Ending Interation"));
}

void AInteractionTestActor::Interact(AStealthPlayerCharacter* playerCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacting"));
	if (winConditionUI)
	{
		winCondition = CreateWidget<UUserWidget>(GetWorld(), winConditionUI);
		winCondition->AddToViewport(10);
		winCondition->SetVisibility(ESlateVisibility::Visible);
	}
}

