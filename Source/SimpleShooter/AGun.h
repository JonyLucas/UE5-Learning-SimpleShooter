// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AAGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGun();
	virtual void Tick(float DeltaTime) override;
	void GetTraceDirection(AController* OwnerController, FVector& Location, FRotator& Rotation, FVector& EndVector);
	void LineTrace(APawn* OwnerPawn, AController* OwnerController, FVector Location, FRotator Rotation,
	               FVector EndVector);
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

};
