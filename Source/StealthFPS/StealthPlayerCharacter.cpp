// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AStealthPlayerCharacter::AStealthPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40, 95);

	turnHorizontalRate = 45;
	turnVerticalRate = 45;

	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->SetupAttachment(GetCapsuleComponent());
	firstPersonCamera->AddRelativeLocation(FVector(-39.65f, 1.75f, 64));
	firstPersonCamera->bUsePawnControlRotation = true;

	bodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	bodyMesh->SetOnlyOwnerSee(true);
	bodyMesh->SetupAttachment(firstPersonCamera);
	bodyMesh->bCastDynamicShadow = false;
	bodyMesh->CastShadow = false;
	bodyMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	bodyMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

// Called when the game starts or when spawned
void AStealthPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStealthPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStealthPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AStealthPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AStealthPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &AStealthPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookVertical"), this, &AStealthPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AStealthPlayerCharacter::Jump);
}

void AStealthPlayerCharacter::FireGun()
{
}

void AStealthPlayerCharacter::MoveForward(float axisValue)
{
	AddMovementInput(GetActorForwardVector() * axisValue);
}

void AStealthPlayerCharacter::MoveRight(float axisValue)
{
	AddMovementInput(GetActorRightVector() * axisValue);
}

void AStealthPlayerCharacter::VerticalTurnAtRate(float rate)
{
}

void AStealthPlayerCharacter::HorizontalTurnAtRate(float rate)
{
}


