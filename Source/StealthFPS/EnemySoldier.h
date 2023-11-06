// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyPatrolPath.h"
#include "EnemySoldier.generated.h"


UCLASS()
class STEALTHFPS_API AEnemySoldier : public ACharacter
{
	GENERATED_BODY()

public:
	//==================================================================
	// PROPERIES AND VARIABLES
	//==================================================================

	virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent, class AController* eventInstigator, AActor* damageCauser);

	UPROPERTY(EditAnywhere)
	class AEnemyAI_Controller* EnemyControllerClass;

	UPROPERTY(EditAnywhere)
	float Health = 100;

	//==================================================================
	// FUNCTIONS
	//==================================================================


	UBehaviorTree* GetBehaviorTree() const;

	AEnemyPatrolPath* GetPatrolPath() const;


	// Sets default values for this character's properties
	AEnemySoldier();

	// Called every frame
	virtual void Tick(float deltaTime) override;

	UFUNCTION()
	void ShootShotGun();
	void EnemyDied();

protected:

	//==================================================================
	// PROPERIES AND VARIABLES
	//==================================================================

	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	//Created the skeletal Mesh Component for the player character in the editor
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* bodyMesh;

	//Created the gun skeletal mesh in the editor
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* gunMesh;

	//Creates location for the muzzle location
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USceneComponent* muzzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	AEnemyPatrolPath* patrolPath;


	//==================================================================
	// FUNCTIONS
	//==================================================================
 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
