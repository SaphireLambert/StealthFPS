// Fill out your copyright notice in the Description page of Project Settings.

// GAME

#include "StealthPlayerCharacter.h"
#include "EnemySoldier.h"
#include "PlayerHealthBar.h"

// ENGINE
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/DamageEvents.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values before instanciation 
AStealthPlayerCharacter::AStealthPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Finn has edited \/

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	turnHorizontalRate = 45;
	turnVerticalRate = 45;

	//Setip for the body mesh
	bodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	bodyMesh->SetOnlyOwnerSee(true);
	bodyMesh->SetupAttachment(firstPersonCamera);
	bodyMesh->bCastDynamicShadow = false;
	bodyMesh->CastShadow = false;
	bodyMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	bodyMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));


	//Setip for the first person camera
	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->SetupAttachment(GetCapsuleComponent());
	firstPersonCamera->SetRelativeLocation(FVector(20, 1.75f, 78));
	firstPersonCamera->bUsePawnControlRotation = true;


	//Setup for the gun mesh
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	gunMesh->SetupAttachment(bodyMesh);
	gunMesh->SetOnlyOwnerSee(true);
	gunMesh->bCastDynamicShadow = false;
	gunMesh->CastShadow = false;

	//Setup for the gun muzzle
	muzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	muzzleLocation->SetupAttachment(gunMesh);
	muzzleLocation->SetRelativeLocation(FVector(0.2f, 22, 9.4f));

	MuzzleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Muzzle Flash"));
	MuzzleEffect->SetupAttachment(muzzleLocation);
	MuzzleEffect->SetAutoActivate(false);

	// Create an audio component
	//audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	//audioComponent->bAutoActivate = false; // Do not play the sound immediately upon creation


	//Setup for the player health
	playerCurrentHealth = playerMaxHealth;

	gunOffset = FVector(100, 0, 10);

	interactioCheckFrequency = 0.1f;
	interactionCheckDistance = 750;

	SetupStimuliSource();

	isAimedIn = false;

	isCrouched = false;

	MaxAmmoReserve = 10;
	MaxAmmmoClip = 1;
	CurrentAmmoReserve = 10;
	CurrentAmmoClip = 1;
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
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AStealthPlayerCharacter::ReloadWeapon);

	PlayerInputComponent->BindAction(TEXT("AimTheGun"), IE_Pressed, this, &AStealthPlayerCharacter::StartZoom);
	PlayerInputComponent->BindAction(TEXT("AimTheGun"), IE_Released, this, &AStealthPlayerCharacter::StopZoom);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AStealthPlayerCharacter::BeginInteract);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &AStealthPlayerCharacter::EndInteract);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AStealthPlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AStealthPlayerCharacter::StopCrouch);
}

// Called when the game starts or when spawned
void AStealthPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	gunMesh->AttachToComponent(bodyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));	

	HUD = Cast<APlayerCharacterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

// Called every frame
void AStealthPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(interactionData.lastInteractionCheckTime) > interactioCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void AStealthPlayerCharacter::PerformInteractionCheck()
{
	interactionData.lastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector startTrace{GetPawnViewLocation()};
	FVector endTrace{startTrace + (GetViewRotation().Vector() * interactionCheckDistance)};

	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if (LookDirection > 0)
	{

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(this);
		FHitResult traceHit;

		if (GetWorld()->LineTraceSingleByChannel(traceHit, startTrace, endTrace, ECC_Visibility, queryParams))
		{
			if (traceHit.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				

				if (traceHit.GetActor() != interactionData.currentInteractable)
				{
					FoundInteractable(traceHit.GetActor());
					return;
				}
				if (traceHit.GetActor() == interactionData.currentInteractable)
				{
					return;
				}
			}
		}
		NoInteractableFound();
	}
}

void AStealthPlayerCharacter::FoundInteractable(AActor* newInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (interactionData.currentInteractable)
	{
		targetInteractable = interactionData.currentInteractable;
		targetInteractable->EndFocus();
	}

	interactionData.currentInteractable = newInteractable;
	targetInteractable = newInteractable;
	
	HUD->UpdateInteractionWidget(&targetInteractable->interactableData);

	targetInteractable->BeginFocus();
}

void AStealthPlayerCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(timerHandle_Interaction);
	}

	if (interactionData.currentInteractable)
	{
		if(IsValid(targetInteractable.GetObject()))
		{
			targetInteractable->EndFocus();
		}
	}

	HUD->HideInteractionWidget();

	interactionData.currentInteractable = nullptr;
	targetInteractable = nullptr;
}

void AStealthPlayerCharacter::BeginInteract()
{

	// Verify nothiong has changed with the interactable state since the begining interaction
	PerformInteractionCheck();

	if (interactionData.currentInteractable)
	{
		if (IsValid(targetInteractable.GetObject()))
		{
			targetInteractable->BeginInteract();
			if (FMath::IsNearlyZero(targetInteractable->interactableData.interactionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(timerHandle_Interaction,
					this,
					&AStealthPlayerCharacter::Interact,
					targetInteractable->interactableData.interactionDuration,
					false);
			}
		}
	}

}

void AStealthPlayerCharacter::EndInteract()
{
	GetWorldTimerManager().ClearTimer(timerHandle_Interaction);

	if (IsValid(targetInteractable.GetObject()))
	{
		targetInteractable->EndInteract();
	}
}

void AStealthPlayerCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(timerHandle_Interaction);

	if (IsValid(targetInteractable.GetObject()))
	{
		targetInteractable->Interact(this);
	}
}

float AStealthPlayerCharacter::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	float damageCaused = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	damageCaused = FMath::Min(playerCurrentHealth, damageCaused);

	playerCurrentHealth -= damageCaused;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Damage caused to player"));

	if (playerCurrentHealth <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Has Died"));
		Destroy();
	}
	
	return damageCaused;
}

void AStealthPlayerCharacter::FireGun()
{
	if (CurrentAmmoClip > 0)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GunShotSilenced, muzzleLocation->GetComponentLocation());
		MuzzleEffect->Activate();
		Projectile();
		CurrentAmmoClip--;
	}
}

void AStealthPlayerCharacter::Projectile()
{
	FHitResult hit;

	const float weaponRange = 2500;
	const FVector startTrace = muzzleLocation->GetComponentLocation();
	const FVector forwardVector = firstPersonCamera->GetForwardVector();
	const FVector endTrace = (forwardVector * weaponRange) + startTrace;

	FCollisionQueryParams queryparameters;
	queryparameters.AddIgnoredActor(this);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OUT hit, startTrace, endTrace, ECC_Camera, queryparameters);

	if (isHit)
	{
		FPointDamageEvent damageEvent(100, hit, forwardVector, nullptr); //Calls the damage event to deal damage to whatever the gun hit
		hit.GetActor()->TakeDamage(100, damageEvent, GetInstigatorController(), this);//Damages the actor that the raycast hit
	}
}

void AStealthPlayerCharacter::ReloadWeapon()
{
	
	
		if (CurrentAmmoClip != MaxAmmmoClip)
		{
			if (CurrentAmmoReserve - (MaxAmmmoClip - CurrentAmmoClip) >= 0)
			{
				CurrentAmmoReserve -= (MaxAmmmoClip - CurrentAmmoClip);
				CurrentAmmoClip = MaxAmmmoClip;
			}
			else
			{
				CurrentAmmoClip += CurrentAmmoReserve;
				CurrentAmmoReserve = 0;
			}
		}
	
}

void AStealthPlayerCharacter::TriggerOutOfAmmoPopUp()
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
	AddControllerYawInput(rate * turnVerticalRate * GetWorld()->GetDeltaSeconds());
}

void AStealthPlayerCharacter::HorizontalTurnAtRate(float rate)
{
	AddControllerPitchInput(rate * turnHorizontalRate * GetWorld()->GetDeltaSeconds());
}

void AStealthPlayerCharacter::SetupStimuliSource()
{
	stimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (stimulusSource)
	{
		stimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		stimulusSource->RegisterWithPerceptionSystem();
	}
}

void AStealthPlayerCharacter::StartZoom()
{	
	firstPersonCamera->SetFieldOfView(70);
	isAimedIn = true;	
}

void AStealthPlayerCharacter::StopZoom()
{
	firstPersonCamera->SetFieldOfView(110);
	isAimedIn = false;
}

void AStealthPlayerCharacter::StartCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(48);
	GetCharacterMovement()->MaxWalkSpeed = 300;
	ACharacter::Crouch();

	isCrouched = true;
}

void AStealthPlayerCharacter::StopCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(95);
	GetCharacterMovement()->MaxWalkSpeed = 600;
	ACharacter::UnCrouch();

	isCrouched = false;
}



