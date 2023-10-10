// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthPlayerCharacter.h"
#include "EnemySoldier.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/DamageEvents.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "LevelObjective.h"
#include "Blueprint/UserWidget.h"

//#include <Subsystems/PanelExtensionSubsystem.h>


// Sets default values before instanciation 
AStealthPlayerCharacter::AStealthPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Finn has edited \/

	GetCapsuleComponent()->InitCapsuleSize(20, 95); // Sets the size for the capsule component for the player character. 

	turnHorizontalRate = 45;
	turnVerticalRate = 45;

	//Setip for the first person camera
	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->SetupAttachment(GetCapsuleComponent());
	firstPersonCamera->SetRelativeLocation(FVector(20, 1.75f, 78));
	firstPersonCamera->bUsePawnControlRotation = true;

	//Setip for the body mesh
	bodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	bodyMesh->SetOnlyOwnerSee(true);
	bodyMesh->SetupAttachment(firstPersonCamera);
	bodyMesh->bCastDynamicShadow = false;
	bodyMesh->CastShadow = false;
	bodyMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	bodyMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//Setup for the gun mesh
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));

	gunMesh->SetOnlyOwnerSee(true);
	gunMesh->bCastDynamicShadow = false;
	gunMesh->CastShadow = false;

	//Setup for the gun muzzle
	muzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));

	muzzleLocation->SetupAttachment(gunMesh);
	muzzleLocation->SetRelativeLocation(FVector(0.2f, 22, 9.4f));

	//Setup for the player health
	playerCurrentHealth = playerMaxHealth;

	gunOffset = FVector(100, 0, 10);

	interactionRange = 300;

	SetupStimuliSource();
}

// Called when the game starts or when spawned
void AStealthPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	gunMesh->AttachToComponent(bodyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));	
}

// Called every frame
void AStealthPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hitresult;
	FCollisionQueryParams collisionRules;
	FVector startlocation = firstPersonCamera->GetComponentLocation();
	FVector endLocation = (firstPersonCamera->GetForwardVector() * interactionRange) + startlocation;
	if (GetWorld()->LineTraceSingleByChannel(hitresult, startlocation, endLocation, ECC_Visibility, collisionRules))
	{

		if (hitresult.bBlockingHit)
		{
		
			if (auto interactableActor = Cast<ALevelObjective>(hitresult.GetActor()))
			{
				interactableActor->DisplayInteractPrompt(interactableActor->GetName());
			}
		}
	}

}

// Called to bind functionality to input
void AStealthPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AStealthPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AStealthPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &AStealthPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookVertical"), this, &AStealthPlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AStealthPlayerCharacter::FireGun);

	//PlayerInputComponent->BindAction(TEXT("Crouch"),IE_Pressed, this, &AStealthPlayerCharacter::Crouch);
	//PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AStealthPlayerCharacter::StopCrouch);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AStealthPlayerCharacter::InteractWithObject);
}

float AStealthPlayerCharacter::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	float damageCaused = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	damageCaused = FMath::Min(playerCurrentHealth, damageCaused);

	playerCurrentHealth -= damageCaused;

	if (playerCurrentHealth <= 0)
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Player has died"));
	}
	
	return damageCaused;
}

void AStealthPlayerCharacter::FireGun()
{
	FHitResult hit;

	const float weaponRange = 2000;
	const FVector startTrace = muzzleLocation->GetComponentLocation();
	const FVector forwardVector = firstPersonCamera->GetForwardVector();
	const FVector endTrace = (forwardVector * weaponRange) + startTrace;

	FCollisionQueryParams queryparameters;
	queryparameters.AddIgnoredActor(this);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OUT hit, startTrace, endTrace, ECC_Camera, queryparameters);


	if (isHit)
	{
		FPointDamageEvent damageEvent(100, hit, forwardVector, nullptr);
		hit.GetActor()->TakeDamage(100, damageEvent, GetInstigatorController(), this);



		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Red, true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit Somthing"));
			
	}
	
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
	AddControllerYawInput(rate * turnVerticalRate * GetWorld()->GetDeltaSeconds());
}

void AStealthPlayerCharacter::HorizontalTurnAtRate(float rate)
{
	AddControllerPitchInput(rate * turnHorizontalRate * GetWorld()->GetDeltaSeconds());
}

void AStealthPlayerCharacter::InteractWithObject()
{

}

void AStealthPlayerCharacter::SetupStimuliSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void AStealthPlayerCharacter::ExitGame()
{

}

//void AStealthPlayerCharacter::Crouch()
//{
//	firstPersonCamera->SetRelativeLocation(FVector(20, 1.75f, 50));
//}
//
//void AStealthPlayerCharacter::StopCrouch()
//{
//	firstPersonCamera->SetRelativeLocation(FVector(20, 1.75f, 78));
//}



