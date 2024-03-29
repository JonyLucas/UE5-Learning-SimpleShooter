// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	AActor* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 200.f;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UBlackboardComponent* BlackboardComponent;
	
};
