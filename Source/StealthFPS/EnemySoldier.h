// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemySoldier.generated.h"


UCLASS()
class STEALTHFPS_API AEnemySoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemySoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float deltaTime) override;


//Finn Edit From Here\/
public:

	UBehaviorTree* GetBehaviorTree() const;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* damageCollision;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, 
		UPrimitiveComponent* otherComp, int32 otherBodyIndex, 
		bool bFromSweep, const FHitResult& hit);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterAttributes)
	float enemyHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterAttributes)
	float damageValue = 100;

	virtual float TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent, class AController* eventInstigator, AActor* damageCauser);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* enemyBehaviourTree;


};
